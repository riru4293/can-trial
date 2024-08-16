#include <stdio.h>

// FreeRTOS
#include <FreeRTOS.h>
#include <task.h>

#include "driver/include/public/driver.h"
#include "logger/include/public/logger.h"

#include "private/irq_task.h"
#include "private/can_rx_task.h"
#include "private/can_tx_task.h"

#define IRQ_SOURCES (UINT8)( DRV_IRQ_CAN_TX0_EMPTY | DRV_IRQ_CAN_RX0_FULL )

/* Prototypes */
static VOID task( VOID* unused_arg );


/* Globals */
static TaskHandle_t task_handle = NULL;


VOID create_irq_task( VOID )
{
    xTaskCreate( task, "IRQ_TASK", 1024, NULL, 7, &task_handle );
}

VOID irq_handler( VOID )
{
    static BaseType_t higher_priority_task_woken = pdFALSE;

    drv_enable_irq( FALSE );

    vTaskNotifyGiveFromISR( task_handle, &higher_priority_task_woken );

    // Exit to context switch if necessary
    portYIELD_FROM_ISR(higher_priority_task_woken);
}


static VOID task( VOID* unused_arg )
{
    const TaskHandle_t can_rx_task_handler = get_can_rx_task_handler();
    const TaskHandle_t can_tx_task_handler = get_can_tx_task_handler();
    UINT8 occurred_irq;

#ifdef DEBUG
    UINT8 tmp;
#endif /* DEBUG */
 
    /* Set callback function for IRQ */
    drv_set_irq_callback( irq_handler );

    /* Enable IRQ */
    drv_enable_irq( TRUE );

    /* Enable IRQ sources */
    drv_enable_irq_sources( IRQ_SOURCES );

    drvtmp_to_normal_mode();

    while( TRUE )
    {
        /* Wait for an IRQ to occur */
        ulTaskNotifyTake( pdTRUE, portMAX_DELAY );

        /* Begin critical section */
        taskENTER_CRITICAL();

        /* Get IRQ sources */
        occurred_irq = drv_get_occurred_irq();

        /* If an IRQ source exists, disable it. */
        /* Because it prevents reentrancy by the same IRQ source */
        if ( DRV_IRQ_NONE != occurred_irq )
        {
            drv_disable_irq_sources( occurred_irq );
        }
#ifdef DEBUG
        else{
            printf("twice");
        }
#endif /* DEBUG */

#ifdef DEBUG
        /* CAN受信オーバーフロー確認 */
        tmp = drvtmp_get_eflg();
        if( tmp & 0xC0 )
            printf("over! %02X", tmp);
#endif /* DEBUG */

        /* End critical section */
        taskEXIT_CRITICAL();

        


        /* Notify the CAN-RX task of CAN reception */
        if( DRV_IRQ_NONE != ( occurred_irq & DRV_IRQ_CAN_RX0_FULL ) )
        {
            xTaskNotifyGive( can_rx_task_handler );
        }

        /* Notify the CAN-TX task that CAN transmission has been completed */
        if( DRV_IRQ_NONE != ( occurred_irq & DRV_IRQ_CAN_TX0_EMPTY ) )
        {
            xTaskNotifyGive( can_tx_task_handler );
        }

        /* Enables a disabled interrupt when an IRQ occurs */
        drv_enable_irq( TRUE );
    }
}
