#include <stdio.h>

// FreeRTOS
#include <FreeRTOS.h>
#include <task.h>

#include "driver/include/public/driver.h"
#include "logger/include/public/logger.h"

#include "private/can_tx_task.h"


/* Prototypes */
static VOID task( VOID* unused_arg );


/* Globals */
static TaskHandle_t task_handle = NULL;


/* temp */
#define SPICMD_READ_RX0_HDR             ( 0x90U )
#define MCP2515_CANHDR_SIDH 0
#define MCP2515_CANHDR_SIDL 1
#define SPICMD_REQ_TX0                  ( 0x81U )
static UINT32 build_std_canid( const UINT8 *hdr );


VOID create_can_tx_task( VOID )
{
    xTaskCreate( task, "CAN_TX_TASK", 1024, NULL, 8, &task_handle );
}


TaskHandle_t get_can_tx_task_handler( VOID )
{
    return task_handle;
}


static VOID task( VOID* unused_arg )
{
    while( TRUE )
    {
        ulTaskNotifyTake( pdTRUE, portMAX_DELAY );

        vTaskSuspendAll();

        /* Clear IRQ factor of the TX0 */
        drv_clear_irq_sources( DRV_IRQ_CAN_TX0_EMPTY );

        /* Request to send. */
        drv_begin_spi();
        drv_write_spi( SPICMD_REQ_TX0 );
        drv_end_spi();

        (VOID)xTaskResumeAll();
    }
}


static UINT32 build_std_canid( const UINT8 *hdr )
{
    return (UINT32)(
        (UINT32)( (UINT32)( (UINT32)hdr[ MCP2515_CANHDR_SIDH ] << 3U ) & 0x000007F8UL )
      | (UINT32)( (UINT32)( (UINT32)hdr[ MCP2515_CANHDR_SIDL ] >> 5U ) & 0x00000007UL )
    );
}
