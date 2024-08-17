#include <stdio.h>

// FreeRTOS
#include <FreeRTOS.h>
#include <task.h>
#include <event_groups.h>

#include "driver/include/public/driver.h"
#include "logger/include/public/logger.h"

#include "public/appl_task.h"


/* Prototypes */
static VOID task( VOID* unused );


/* Globals */
static TaskHandle_t task_handle = NULL;
static EventGroupHandle_t event_handle;

/* temp */
#define SPICMD_READ_RX0_HDR             ( 0x90U )
#define MCP2515_CANHDR_SIDH 0
#define MCP2515_CANHDR_SIDL 1
static UINT32 build_std_canid( const UINT8 *hdr );


EventGroupHandle_t canrx_get_event_handle( VOID )
{
    return event_handle;
}


VOID create_can_rx_task( VOID )
{
    xTaskCreate( task, "CAN_RX_TASK", 1024, NULL, CAN_RX_TASK_PRIORITY, &task_handle );
}


TaskHandle_t get_can_rx_task_handler( VOID )
{
    return task_handle;
}


static VOID task( VOID* unused )
{
    EventBits_t events;
    UINT32 rxid;
    UINT8 rxhdr[ 5 ] = { 0U };
    UINT8 rxbdy[ 8 ] = { 0U };

    event_handle = xEventGroupCreate();

    while( TRUE )
    {
        events = xEventGroupWaitBits( event_handle, 0x01U, pdTRUE, pdFALSE, portMAX_DELAY );

        /* Begin prohibiting task switching */
        vTaskSuspendAll();

#ifdef DEBUG
        /* Read CAN header from register. */
        drv_begin_spi();
        drv_write_spi( SPICMD_READ_RX0_HDR );
        drv_read_array_spi( 5U, rxhdr );
        drv_end_spi();

        rxid = build_std_canid( rxhdr );
#endif

        drv_clear_occurred_irq( DRV_IRQ_CAN_RX0_FULL );
        drv_enable_irq_factor( DRV_IRQ_CAN_RX0_FULL );

        /* End prohibiting task switching */
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
