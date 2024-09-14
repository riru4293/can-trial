// /* -------------------------------------------------------------------------- */
// /* Include                                                                    */
// /* -------------------------------------------------------------------------- */
// /* RP2040 */
// #include <hardware/spi.h>
// #include <pico/stdlib.h>

// /* APPL */
// #include <public/hardware_driver.h>

// /* -------------------------------------------------------------------------- */
// /* Macro                                                                      */
// /* -------------------------------------------------------------------------- */
// /* GPIO status */
// #define GPIO_VOLT_LOW           ( FALSE )
// #define GPIO_VOLT_HIGH          ( TRUE )

// /* GPIO pin number */
// #define GPIO_IDX_SPI_0_MISO     ( (UINT) 4U )
// #define GPIO_IDX_SPI_0_CS       ( (UINT) 5U )
// #define GPIO_IDX_SPI_0_SCK      ( (UINT) 6U )
// #define GPIO_IDX_SPI_0_MOSI     ( (UINT) 7U )
// #define GPIO_IDX_CAN_IRQ        ( (UINT)21U )
// #define GPIO_IDX_LED            ( (UINT)25U )

// /* SPI hardware */
// #define SPI_0_HW                ( spi0 )
// #define SPI_1_HW                ( spi1 )

// /* Maximum configurable SPI clock: 8.928571MHz.                                     */
// /* The maximum SPI clock for the MCP2515 is 10MHz, but this is not configurable.    */
// /* Because the SPI clock cannot be set to any value other than the division value   */
// /* of the RP2040 frequency that 125 MHz.                                            */
// #define SPI_0_BAUDRATE          ( (UINT)8928571U )

// /* The value that will be set in the SPI send buffer when reading the SPI receive buffer */
// #define SPI_REPEATED_TX_DATA    ( (UINT8)0U )

// /* -------------------------------------------------------------------------- */
// /* Prototype                                                                  */
// /* -------------------------------------------------------------------------- */
// static VOID enable_irq_handling( BOOL enabled );
// static VOID irq_callback( UINT gpio, UINT32 events );
// static VOID init_spi_0_hw( VOID );
// static VOID begin_spi_0( VOID );
// static VOID end_spi_0( VOID );
// static VOID read_spi_0_array( const SIZE_T len, UINT8 *buff );
// static VOID write_spi_0_array( const SIZE_T len, const UINT8 const *buff );
// static VOID read_spi_0( VOID );
// static VOID write_spi_0( const UINT8 val );

// /* -------------------------------------------------------------------------- */
// /* Global                                                                     */
// /* -------------------------------------------------------------------------- */
// static hwdrv_irq_callback_t g_irq_callback = NULL;

// /* -------------------------------------------------------------------------- */
// /* Public function                                                            */
// /* -------------------------------------------------------------------------- */
// VOID hwdrv_init_hardware( VOID )
// {
//     /* Initialize standard I/O */
//     stdio_init_all();

//     /* Initialize LED */
//     gpio_init(GPIO_IDX_LED);
//     gpio_set_dir(GPIO_IDX_LED, GPIO_OUT);

//     /* Initialize SPI */
//     init_spi_0_hw();
// }

// ERR_CD_T hwdrv_reset_can_controller( VOID )
// {
//     begin_spi_0();

//     write_spi_0( SPICMD_RESET );

//     end_spi_0();

//     while( 0x80U != ( read_reg( REG_CANSTAT ) & 0xE0U ) ); /* Wait reset comp */

//     /* CAN baudrate 125Kbps */
//     configure_can_baudrate();

//     /* 受信バッファ１設定。すべて受信。RX1への切り替え禁止。 *5/
//     write_reg( REG_RXB0CTRL, 0x60 );

//     /* 受信バッファ２設定。フィルタ一致のみ受信。 */
//     write_reg( REG_RXB1CTRL, 0x00 );
// }

// VOID hwdrv_turn_on_led( VOID )
// {
//     gpio_put( GPIO_IDX_LED, GPIO_VOLT_HIGH );
// }

// VOID hwdrv_turn_off_led( VOID )
// {
//     gpio_put( GPIO_IDX_LED, GPIO_VOLT_LOW );
// }

// VOID hwdrv_set_irq_callback( hwdrv_irq_callback_t callback )
// {
//     g_irq_callback = callback;
// }

// VOID hwdrv_enable_can_irq_handling( VOID )
// {
//     enable_irq_handling( TRUE );
// }

// VOID hwdrv_disable_can_irq_handling( VOID )
// {
//     enable_irq_handling( FALSE );
// }

// /* -------------------------------------------------------------------------- */
// /* Private functions                                                          */
// /* -------------------------------------------------------------------------- */
// static VOID enable_irq_handling( BOOL enabled )
// {
//     gpio_set_irq_enabled_with_callback(
//         GPIO_IDX_CAN_IRQ, GPIO_IRQ_LEVEL_LOW, enabled, irq_callback );
// }

// static VOID irq_callback( UINT gpio, UINT32 events )
// {
//     if( ( NULL != g_irq_callback )
//         && ( GPIO_IDX_CAN_IRQ == gpio )
//         && ( GPIO_IRQ_LEVEL_LOW == events ) )
//     {
//         g_irq_callback();
//     }
// }

// static VOID init_spi_0_hw( VOID )
// {
//     (VOID)spi_init( SPI_0_HW, SPI_0_BAUDRATE );

//     gpio_set_function( GPIO_IDX_SPI_0_MISO, GPIO_FUNC_SPI );
//     gpio_set_function( GPIO_IDX_SPI_0_MOSI, GPIO_FUNC_SPI );
//     gpio_set_function( GPIO_IDX_SPI_0_SCK,  GPIO_FUNC_SPI );

//     gpio_init( GPIO_IDX_SPI_0_CS );
//     gpio_set_dir( GPIO_IDX_SPI_0_CS, GPIO_OUT );
// }

// static VOID begin_spi_0( VOID )
// {
//     gpio_put( GPIO_IDX_SPI_0_CS, GPIO_VOLT_LOW );
// }

// static VOID end_spi_0( VOID )
// {
//     gpio_put( GPIO_IDX_SPI_0_CS, GPIO_VOLT_HIGH );
// }

// static VOID read_spi_0_array( const SIZE_T len, UINT8 *buff )
// {
//     if( ( 0U < len ) && ( NULL != buff ) )
//     {
//         (VOID)spi_read_blocking( SPI_0_HW, SPI_REPEATED_TX_DATA, buff, len );
//     }
// }

// static VOID write_spi_0_array( const SIZE_T len, const UINT8 const *buff )
// {
//     if( ( 0U < len ) && ( NULL != buff ) )
//     {
//         (VOID)spi_write_blocking( SPI_0_HW, buff, len );
//     }
// }

// static VOID read_spi_0( VOID )
// {
//     UINT8 val;

//     read_spi_0_array( sizeof( UINT8 ), &val );

//     return val;
// }

// static VOID write_spi_0( const UINT8 val )
// {
//     write_spi_0_array( sizeof( UINT8 ), &val );
// }
