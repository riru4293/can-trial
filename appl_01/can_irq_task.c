#include <stdio.h>

// FreeRTOS
#include <FreeRTOS.h>
#include <task.h>
#include <event_groups.h>

#include "driver/include/public/driver.h"
#include "logger/include/public/logger.h"

#include "public/appl_task.h"

#define ENABLED_IRQ_FACTORS (UINT8)(\
  DRV_IRQ_CAN_TX0_EMPTY | DRV_IRQ_CAN_TX1_EMPTY | DRV_IRQ_CAN_TX2_EMPTY \
| DRV_IRQ_CAN_RX0_FULL  | DRV_IRQ_CAN_RX1_FULL )

/* Prototypes */
static VOID task( VOID* unused );
static VOID irq_callback( VOID );
static VOID init( VOID );


/* Globals */
static TaskHandle_t task_handle = NULL;

VOID canirq_create_task( VOID )
{
    xTaskCreate( task, "CAN_IRQ_TASK", 1024, NULL, CAN_IRQ_TASK_PRIORITY, &task_handle );
}


TaskHandle_t canirq_get_task_handler( VOID )
{
    return task_handle;
}



/* -------------------------------------------------------------------------- */
/* Private functions                                                          */
/* -------------------------------------------------------------------------- */
static VOID task( VOID* unused )
{
    EventGroupHandle_t can_rx_event_handle;
    EventGroupHandle_t can_tx_event_handle;

    drv_irq_t occurred_irq;
 
    /* Initialize this task */
    init();

    while( TRUE )
    {
        /* Wait an IRQ occurred */
        ulTaskNotifyTake( pdTRUE, portMAX_DELAY );

        /* Get occurred IRQ */
        occurred_irq = drv_get_occurred_irq();

        /* If an IRQ occurred, disable it factor. */
        /* Because it prevents reentrancy by the same IRQ factor. */
        if ( DRV_IRQ_NONE != occurred_irq )
        {
            drv_disable_irq_factor( occurred_irq );
        }

        /* Notify the CAN-RX task of CAN reception */
        if( DRV_IRQ_NONE != (drv_irq_t)( occurred_irq & DRV_IRQ_CAN_RX0_FULL ) )
        {
            can_rx_event_handle = canrx_get_event_handle();
            xEventGroupSetBits( can_rx_event_handle, 0x01U );
        }

        /* Notify the CAN-TX task that CAN transmission has been completed */
        if( DRV_IRQ_NONE != (drv_irq_t)( occurred_irq & DRV_IRQ_CAN_TX0_EMPTY ) )
        {
            can_tx_event_handle = cantx_get_event_handle();
            xEventGroupSetBits( can_tx_event_handle, 0x01U );
        }

        /* Enable a disabled IRQ handling when an IRQ occurred */
        drv_enable_irq_handling();
    }
}


static VOID init( VOID )
{
    /* Set callback function for IRQ */
    drv_set_irq_callback( irq_callback );

    /* Enable IRQ handling */
    drv_enable_irq_handling();

    /* Enable IRQ factor */
    drv_enable_irq_factor( ENABLED_IRQ_FACTORS );

    /* Run CAN network */
    drvtmp_to_normal_mode();
}


static VOID irq_callback( VOID )
{
    static BaseType_t higher_priority_task_woken = pdFALSE;

    /* Prevent continuous occurs IRQ */
    drv_disable_irq_handling();

    /* Notify to task 'CAN_IRQ_TASK' */
    vTaskNotifyGiveFromISR( task_handle, &higher_priority_task_woken );

    /* Exit to context switch if necessary */
    portYIELD_FROM_ISR( higher_priority_task_woken );
}
