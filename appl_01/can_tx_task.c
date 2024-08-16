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
#define SPICMD_REQ_TX0                  ( 0x81U )


VOID create_can_tx_task( VOID )
{
    xTaskCreate( task, "CAN_TX_TASK", 1024, NULL, 5, &task_handle );
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

        /* Begin prohibiting task switching */
        vTaskSuspendAll();

        drv_clear_occurred_irq( DRV_IRQ_CAN_TX0_EMPTY );
        drv_enable_irq_sources( DRV_IRQ_CAN_TX0_EMPTY );

        /* Request to send. */
        drv_begin_spi();
        drv_write_spi( SPICMD_REQ_TX0 );
        drv_end_spi();

        /* End prohibiting task switching */
        (VOID)xTaskResumeAll();
    }
}
