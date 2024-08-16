#include <stdio.h>

// FreeRTOS
#include <FreeRTOS.h>
#include <task.h>

#include "driver/include/public/driver.h"
#include "logger/include/public/logger.h"

#include "public/appl_task.h"

#define IRQ_SOURCES (UINT8)( DRV_IRQ_CAN_TX0_EMPTY | DRV_IRQ_CAN_RX0_FULL )

/* Prototypes */
static VOID task( VOID* unused );


/* Globals */
static TaskHandle_t task_handle = NULL;


TaskHandle_t get_irq_task_handler( VOID )
{
    return task_handle;
}


VOID create_irq_task( VOID )
{
    xTaskCreate( task, "IRQ_TASK", 1024, NULL, 7, &task_handle );
}

VOID irq_handler( VOID )
{
    static BaseType_t higher_priority_task_woken = pdFALSE;

    drv_disable_irq_handling();

    vTaskNotifyGiveFromISR( task_handle, &higher_priority_task_woken );

    // Exit to context switch if necessary
    portYIELD_FROM_ISR(higher_priority_task_woken);
}


static VOID task( VOID* unused )
{
    const TaskHandle_t can_rx_task_handler = get_can_rx_task_handler();
    const TaskHandle_t can_tx_task_handler = get_can_tx_task_handler();
    drv_irq_t irq_occurrence;

#ifdef DEBUG
    drv_err_t tmp;
#endif /* DEBUG */
 
    /* Set callback function for IRQ */
    drv_set_irq_handler( irq_handler );

    /* Enable IRQ */
    drv_enable_irq_handling();

    /* Enable IRQ sources */
    drv_enable_irq_factor( IRQ_SOURCES );

    drvtmp_to_normal_mode();

    while( TRUE )
    {
        /* Wait for an IRQ to occur */
        ulTaskNotifyTake( pdTRUE, portMAX_DELAY );

        /* Begin critical section */
        taskENTER_CRITICAL();

        /* Get IRQ sources */
        irq_occurrence = drv_get_irq_occurrence();

        /* If an IRQ source exists, disable it. */
        /* Because it prevents reentrancy by the same IRQ source */
        if ( DRV_IRQ_NONE != irq_occurrence )
        {
            drv_disable_irq_factor( irq_occurrence );
        }
#ifdef DEBUG
        else{
            printf("twice");
        }
#endif /* DEBUG */

#ifdef DEBUG
        /* CAN受信オーバーフロー確認 */
        tmp = drv_get_err_occurrence();
        if( tmp & 0xC0 )
            printf("over! %02X", tmp);
#endif /* DEBUG */

        /* End critical section */
        taskEXIT_CRITICAL();

        


        /* Notify the CAN-RX task of CAN reception */
        if( DRV_IRQ_NONE != ( irq_occurrence & DRV_IRQ_CAN_RX0_FULL ) )
        {
            xTaskNotifyGive( can_rx_task_handler );
        }

        /* Notify the CAN-TX task that CAN transmission has been completed */
        if( DRV_IRQ_NONE != ( irq_occurrence & DRV_IRQ_CAN_TX0_EMPTY ) )
        {
            xTaskNotifyGive( can_tx_task_handler );
        }

        /* Enables a disabled interrupt when an IRQ occurs */
        drv_enable_irq_handling();
    }
}
