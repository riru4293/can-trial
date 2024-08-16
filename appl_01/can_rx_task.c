#include <stdio.h>

// FreeRTOS
#include <FreeRTOS.h>
#include <task.h>

#include "driver/include/public/driver.h"
#include "logger/include/public/logger.h"

#include "private/can_rx_task.h"


/* Prototypes */
static VOID task( VOID* unused_arg );


/* Globals */
static TaskHandle_t task_handle = NULL;


/* temp */
#define SPICMD_READ_RX0_HDR             ( 0x90U )
#define MCP2515_CANHDR_SIDH 0
#define MCP2515_CANHDR_SIDL 1
static UINT32 build_std_canid( const UINT8 *hdr );


VOID create_can_rx_task( VOID )
{
    xTaskCreate( task, "CAN_RX_TASK", 1024, NULL, 6, &task_handle );
}


TaskHandle_t get_can_rx_task_handler( VOID )
{
    return task_handle;
}


static VOID task( VOID* unused_arg )
{
    UINT32 rxid;
    UINT8 rxhdr[ 5 ] = { 0U };
    UINT8 rxbdy[ 8 ] = { 0U };

    while( TRUE )
    {
        ulTaskNotifyTake( pdTRUE, portMAX_DELAY );

        vTaskSuspendAll();

        /* Read CAN header from register. */
        drv_begin_spi();
        drv_write_spi( SPICMD_READ_RX0_HDR );
        drv_read_array_spi( 5U, rxhdr );
        drv_end_spi();

        (VOID)xTaskResumeAll();

        rxid = build_std_canid( rxhdr );

        drv_clear_occurred_irq( DRV_IRQ_CAN_RX0_FULL );
        drv_enable_irq_sources( DRV_IRQ_CAN_RX0_FULL );
    }
}


static UINT32 build_std_canid( const UINT8 *hdr )
{
    return (UINT32)(
        (UINT32)( (UINT32)( (UINT32)hdr[ MCP2515_CANHDR_SIDH ] << 3U ) & 0x000007F8UL )
      | (UINT32)( (UINT32)( (UINT32)hdr[ MCP2515_CANHDR_SIDL ] >> 5U ) & 0x00000007UL )
    );
}
