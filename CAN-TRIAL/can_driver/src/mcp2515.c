#include "pico/stdlib.h"
#include "spi_wrapper_api.h"
#include "can_driver_api.h"
#include "mcp2515.h"

// /*! 
//  * \defgroup GpioLogic GPIO logic
//  */
// /*! \{ */
// #define PORT_LOW          ( (uint8_t)0U ) /*!< Negative logic */
// #define PORT_HIGH         ( (uint8_t)1U ) /*!< Positive logic */
// /*! \} */



#define SPI_REPEATED_TX_DATA         ( (uint8_t)0U )

/*!
 * @brief Time out of change operation mode.
 */
#define TIMEOUTOF_OPMODE_CHANGE   ( 1000000UL )       /*!< 1s */

// static void begin_spi( void );
// static void end_spi( void );
// static void read_spi_array( const size_t n, uint8_t *buf );
// static void write_spi( const uint8_t val );
// static void write_spi_array( const size_t n, const uint8_t const *buf );
static void read_reg_array( const uint8_t addr, const size_t n, uint8_t *buf );
static void write_reg_array( const uint8_t addr, const size_t n, const uint8_t const *buf );
static uint8_t read_reg( const uint8_t addr );
static void write_reg( const uint8_t addr, const uint8_t val );
static void modify_reg( const uint8_t addr, const uint8_t mask, const uint8_t val );

// void mcp2515_reset( void );

static bool is_valid_opmode( const uint8_t opmode );
static void disable_wakeup_interrupt( void );
static void enable_wakeup_interrupt( void );
static void allow_wakeup_interrupt( void );
static cd_result_t wait_until_change_opmode( const uint8_t exp_opmode );
static void wakeup( void );

// SPI経由操作は隠蔽
// レジスタ操作も隠蔽

// 公開
// - 受信マスク１からN
// 送信値セット、送信、受信、
// バスオフ判断
// 受信あり判断
// 状態取得
// 割り込み提供？
// エラー取得

// require: suspend_task_switch
// require: stdio_init_all
// note: There will be a maximum wait time of 1 second.
cd_result_t cd_init( void )
{
    cd_result_t ret;

    spiwrp_init();

    /* Reset CAN controler. */
    if( CD_SUCCESS != cd_reset() ) {
        return CD_FAILURE;
    }

    // Set baudlate
    write_reg_array( REG_CNF3, sizeof( CAN_BAUDRATE_500KBPS ), CAN_BAUDRATE_500KBPS );

    // Crear buffers
    // Setup recv mask
 
    if( CD_SUCCESS != wait_until_change_opmode( OPMODE_NORMAL ) )
    {
        return CD_FAILURE;
    }

    return CD_SUCCESS;
}

// require: suspend_task_switch
cd_result_t cd_reset( void )
{
    spiwrp_begin();
    spiwrp_write( SPICMD_RESET );
    spiwrp_end();

    /* ************************************** */
    /* Once the reset is complete,            */
    /* the device will switch to CONFIG mode, */
    /* so wait until then.                    */
    /* ************************************** */
    return wait_until_change_opmode( CD_OPMODE_CONFIG );
}

// require: suspend_task_switch
// require: cd_init
uint8_t cd_get_opmode( void )
{
    uint8_t ret;
    uint8_t canstat;

    canstat = read_reg( REG_CANSTAT );
    ret = (uint8_t)( canstat & MASKOF_CANSTAT_OPMOD );

    return ret;
}

// require: suspend_task_switch
// require: cd_init
// note: There will be a maximum wait time of 1 second.
cd_result_t cd_set_opmode( const uint8_t next_opmode )
{
    uint8_t current_opmode;

    /* Return failure if invalid argument. */
    if( false == is_valid_opmode( next_opmode ) )
        return CD_FAILURE;
    
    /* Get current operation mode. */
    current_opmode = cd_get_opmode();

    /* Return success without doing anything if operation mode is not changed. */
    if( current_opmode == next_opmode )
        return CD_SUCCESS;
    
    /* If the current operating mode is SLEEP, it will wakeup. */
    if( OPMODE_SLEEP == current_opmode )
        wakeup();
    
    /* If the next operating mode is SLEEP, disable wakeup interrupt. */
    if( OPMODE_SLEEP == next_opmode )
        disable_wakeup_interrupt();

    /* Apply next operation mode. */
    modify_reg( REG_CANCTRL, MASKOF_CANSTAT_OPMOD, next_opmode );

    /* Wait until applied the operation mode. */
    return wait_until_change_opmode( next_opmode );
}

static bool is_valid_opmode( const uint8_t opmode )
{
    bool ret;

    switch( opmode )
    {
        case CD_OPMODE_NORMAL:
        case CD_OPMODE_SLEEP:
        case CD_OPMODE_LOOPBACK:
        case CD_OPMODE_LISTENONLY:
        case CD_OPMODE_CONFIG:
            ret = true;
            break;
        default:
            ret = false;
            break;
    }

    return ret;
}

static void disable_wakeup_interrupt( void )
{
    modify_reg( REG_CANINTF, MASKOF_CANINT_WAKIF, REGVAL_ALLBIT_OFF );
}

static void enable_wakeup_interrupt( void )
{
    modify_reg( REG_CANINTF, MASKOF_CANINT_WAKIF, REGVAL_ALLBIT_ON );
}

static void allow_wakeup_interrupt( void )
{
    modify_reg( REG_CANINTE, MASKOF_CANINT_WAKIF, REGVAL_ALLBIT_ON );
}

static cd_result_t wait_until_change_opmode( const uint8_t exp_opmode )
{
    const uint32_t begun = time_us_32();
    uint8_t current_opmode;

    do {
        /* Get current operation mode. */
        current_opmode = cd_get_opmode();

        const uint32_t now = time_us_32();
        const uint32_t elapsed = ( now < begun )
            ? ( UINT32_MAX - begun + now + 1UL )
            : ( now - begun );

        /* Return failure if timeout. */
        if ( elapsed > TIMEOUTOF_OPMODE_CHANGE )
            return CD_FAILURE;

    } while ( exp_opmode != current_opmode );

    return CD_SUCCESS;
}

static void wakeup( void )
{
    const uint8_t origin_caninte = read_reg( REG_CANINTE );

    /* Disable wakeup interrupt. */
    disable_wakeup_interrupt();

    /* Temporarily grants wakeup interrupt permission. */
    allow_wakeup_interrupt();

    /* Enable wakeup interrupt. */
    enable_wakeup_interrupt();

    /* Switch to listen-only mode. Otherwise won't wakeup. */
    cd_set_opmode( OPMODE_LISTENONLY );

    /* Restore wakeup interrupt permission. */
    modify_reg( REG_CANINTE, MASKOF_CANINT_WAKIF, origin_caninte );

    /* Disable wakeup interrupt. */
    disable_wakeup_interrupt();
}

static void read_reg_array( const uint8_t addr, const size_t n, uint8_t *buf )
{
    spiwrp_begin();

    spiwrp_write( SPICMD_READ_REG );
    spiwrp_write( addr );
    spiwrp_read_array( n, buf );

    spiwrp_end();
}
static uint8_t read_reg( const uint8_t addr )
{
    uint8_t val = REGVAL_ALLBIT_ON;

    read_reg_array( addr, sizeof( uint8_t ), &val );

    return val;
}
static void write_reg_array( const uint8_t addr, const size_t n, const uint8_t const *buf )
{
    spiwrp_begin();

    spiwrp_write( SPICMD_WRITE_REG );
    spiwrp_write( addr );
    spiwrp_write_array( n, buf );

    spiwrp_end();
}
static void write_reg( const uint8_t addr, const uint8_t val )
{
    write_reg_array( addr, sizeof( uint8_t ), &val );
}
static void modify_reg( const uint8_t addr, const uint8_t mask, const uint8_t val )
{
    spiwrp_begin();

    spiwrp_write( SPICMD_MODBITS_REG );
    spiwrp_write( addr );
    spiwrp_write( mask );
    spiwrp_write( val );

    spiwrp_end();
}
