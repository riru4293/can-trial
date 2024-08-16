#include <stdio.h>

// FreeRTOS
#include <FreeRTOS.h>
#include <task.h>
#include <timers.h>

#include "driver/include/public/driver.h"
#include "logger/include/public/logger.h"

#include "public/appl_task.h"


/* Prototypes */
static VOID task( VOID* unused );


/* Globals */
static TaskHandle_t task_handle = NULL;


/* temp */
#ifdef DEBUG
#define SPICMD_REQ_TX0                  ( 0x81U )
TimerHandle_t xAutoReloadTimer;
VOID autoReloadTimerCallback( TimerHandle_t xTimer );
BaseType_t xTimer2Started; 
#endif


VOID create_can_tx_task( VOID )
{
    xTaskCreate( task, "CAN_TX_TASK", 1024, NULL, 5, &task_handle );
}


TaskHandle_t get_can_tx_task_handler( VOID )
{
    return task_handle;
}


#ifdef DEBUG
    VOID autoReloadTimerCallback( TimerHandle_t xTimer )
    {
        printf("tick: %d\n", time_us_32());
    }
#endif


static VOID task( VOID* unused )
{
#ifdef DEBUG
    xAutoReloadTimer = xTimerCreate("Reload" , 1000, pdTRUE , NULL, autoReloadTimerCallback);
    xTimer2Started = xTimerStart( xAutoReloadTimer, 0 ); 
#endif
    while( TRUE )
    {
        ulTaskNotifyTake( pdTRUE, portMAX_DELAY );

        /* Begin prohibiting task switching */
        vTaskSuspendAll();

        drv_clear_irq_occurrence( DRV_IRQ_CAN_TX0_EMPTY );
        drv_enable_irq_factor( DRV_IRQ_CAN_TX0_EMPTY );

        /* Request to send. */
        drv_begin_spi();
        drv_write_spi( SPICMD_REQ_TX0 );
        drv_end_spi();

        /* End prohibiting task switching */
        (VOID)xTaskResumeAll();
    }
}
