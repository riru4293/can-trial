#include "driver/include/public/driver.h"
#include "logger/include/public/logger.h"

#include "private/main.h"

#define SPICMD_READ_REG                 ( 0x03U )
#define REG_EFLG                        ( 0x2DU )

static UINT8 read_reg( const UINT8 addr );

static UINT8 eflg = 0x00U;

static UINT8 bus_stat = 0U;
static UINT8 msg_bus_off[]     = "Bus-off";
static UINT8 msg_err_passive[] = "Err-psv";
static UINT8 msg_err_active[]  = "Err-act";

VOID temp_task(VOID* unused) {

    TickType_t xLastWakeTime;
    const TickType_t xFrequency = 1000;
    xLastWakeTime = xTaskGetTickCount();//初期値のセット

    while ( TRUE ) {

        vTaskDelayUntil( &xLastWakeTime, xFrequency );
        
        vTaskSuspendAll();

        eflg = read_reg( REG_EFLG );
        
        (VOID)xTaskResumeAll();
        

        if( 0 < ( eflg & 0x20 ) )
        {
            // Bus-off
            if( 3U != bus_stat )
            {
                bus_stat = 3U;
                (VOID)log_put_msg( sizeof( msg_bus_off ), msg_bus_off );
            }
        }
        else if( 0 < ( eflg & 0x18 ) )
        {
            // Error-passive
            if( 2U != bus_stat )
            {
                bus_stat = 2U;
                (VOID)log_put_msg( sizeof( msg_err_passive ), msg_err_passive );
            }
        }
        else
        {
            // Error-active
            if( 1U != bus_stat )
            {
                bus_stat = 1U;
                (VOID)log_put_msg( sizeof( msg_err_active ), msg_err_active );
            }
        }
    }
}

static UINT8 read_reg( const UINT8 addr ) {
    UINT8 val;
    drv_begin_spi();
    drv_write_spi( SPICMD_READ_REG );
    drv_write_spi( addr );
    drv_read_array_spi( sizeof( val ), &val );
    drv_end_spi();
    return val;
}


