#include <stdio.h>

// FreeRTOS
#include <FreeRTOS.h>
#include <task.h>

#include "driver/include/public/driver.h"
#include "logger/include/public/logger.h"

#include "private/irq_task.h"

static VOID task( VOID* unused_arg );


static TaskHandle_t task_handle = NULL;


/* temp */
#define SPICMD_READ_RX0_HDR             ( 0x90U )
static UINT32 build_std_canid( const UINT8 *hdr );
#define MCP2515_CANHDR_SIDH 0
#define MCP2515_CANHDR_SIDL 1


VOID create_irq_task( VOID )
{
    xTaskCreate( task, "IRQ_TASK", 1024, NULL, 1, &task_handle );
}


VOID irq_handler( VOID ) {
    drv_enable_irq( FALSE );
    
    static BaseType_t higher_priority_task_woken = pdFALSE;
    vTaskNotifyGiveFromISR( task_handle, &higher_priority_task_woken );

    // Exit to context switch if necessary
    portYIELD_FROM_ISR(higher_priority_task_woken);
}


static VOID task(VOID* unused_arg)
{
    UINT32 rxid;
    static UINT8 rxhdr[ 5 ] = { 0U };
    static UINT8 rxbdy[ 8 ] = { 0U };
    static UINT8 mbuf[30] = { 0 };
 
    drv_set_irq_callback( irq_handler );
    drv_enable_irq( TRUE );

    while( TRUE )
    {
        ulTaskNotifyTake( pdTRUE, portMAX_DELAY );


        // 受信しょりBy割り込み
        {
            vTaskSuspendAll();

            /* Read CAN header from register. */
            drv_begin_spi();
            drv_write_spi( SPICMD_READ_RX0_HDR );
            drv_read_array_spi( 5U, rxhdr );
            drv_end_spi();

            (VOID)xTaskResumeAll();

            rxid = build_std_canid( rxhdr );

            sprintf( mbuf, "CAN 0x%x", rxid );
            log_put_msg( 30, mbuf );

            drv_clear_irq_sources( DRV_IRQ_CAN_RX0_FULL );
            drv_enable_irq( TRUE );
        }
    }
}

static UINT32 build_std_canid( const UINT8 *hdr )
{
    return (UINT32)(
        (UINT32)( (UINT32)( (UINT32)hdr[ MCP2515_CANHDR_SIDH ] << 3U ) & 0x000007F8UL )
      | (UINT32)( (UINT32)( (UINT32)hdr[ MCP2515_CANHDR_SIDL ] >> 5U ) & 0x00000007UL )
    );
}
