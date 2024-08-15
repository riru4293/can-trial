#include <stdio.h>

// FreeRTOS
#include <FreeRTOS.h>
#include <task.h>

#include "driver/include/public/driver.h"
#include "logger/include/public/logger.h"

#include "private/irq_task.h"
#include "private/can_rx_task.h"
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


VOID create_irq_task( VOID )
{
    xTaskCreate( task, "IRQ_TASK", 1024, NULL, 7, &task_handle );
}


VOID irq_handler( VOID ) {
    drv_enable_irq( FALSE );
    
    static BaseType_t higher_priority_task_woken = pdFALSE;
    vTaskNotifyGiveFromISR( task_handle, &higher_priority_task_woken );

    // Exit to context switch if necessary
    portYIELD_FROM_ISR(higher_priority_task_woken);
}


static VOID task( VOID* unused_arg )
{
    BaseType_t require_task_switch = pdFALSE;
    BaseType_t tmp_require_task_switch = pdFALSE;
    TaskHandle_t handle;

    UINT32 rxid;
    UINT8 rxhdr[ 5 ] = { 0U };
    UINT8 rxbdy[ 8 ] = { 0U };
    UINT8 mbuf[30] = { 0 };
    UINT8 intf;
 
    drv_set_irq_callback( irq_handler );
    drv_enable_irq( TRUE );

    while( TRUE )
    {
        ulTaskNotifyTake( pdTRUE, portMAX_DELAY );

        require_task_switch = pdFALSE;
        tmp_require_task_switch = pdFALSE;

        vTaskSuspendAll();
        intf = drv_get_irq_sources();
        (VOID)xTaskResumeAll();


        // 受信しょりBy割り込み
        if( DRV_IRQ_NONE != ( intf & DRV_IRQ_CAN_RX0_FULL ) )
        {
            handle = get_can_rx_task_handler();

            xTaskNotifyGive( handle );
        }

        // 送信済みの場合
        if( DRV_IRQ_NONE != ( intf & DRV_IRQ_CAN_TX0_EMPTY ) )
        {
            handle = get_can_tx_task_handler();

            xTaskNotifyGive( handle );
        }

        drv_enable_irq( TRUE );
    }
}


static UINT32 build_std_canid( const UINT8 *hdr )
{
    return (UINT32)(
        (UINT32)( (UINT32)( (UINT32)hdr[ MCP2515_CANHDR_SIDH ] << 3U ) & 0x000007F8UL )
      | (UINT32)( (UINT32)( (UINT32)hdr[ MCP2515_CANHDR_SIDL ] >> 5U ) & 0x00000007UL )
    );
}
