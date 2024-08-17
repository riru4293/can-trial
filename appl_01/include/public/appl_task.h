#ifndef APPL_TASK_H
#define APPL_TASK_H


/* -------------------------------------------------------------------------- */
/* Includes                                                                   */
/* -------------------------------------------------------------------------- */
/* System */

/* PICO-SDK */

/* FreeRTOS */
#include <task.h>

/* APPL */
#include "appl_common.h"


/* -------------------------------------------------------------------------- */
/* Definitions                                                                */
/* -------------------------------------------------------------------------- */
#define MAXOF_TASK_PRIORITY ( configTIMER_TASK_PRIORITY - 1 )
#define IRQ_TASK_PRIORITY   ( MAXOF_TASK_PRIORITY )

/* -------------------------------------------------------------------------- */
/* Prototypes                                                                 */
/* -------------------------------------------------------------------------- */
VOID create_can_init_task( VOID );
TaskHandle_t get_can_init_task_handler( VOID );
VOID request_reset_can_controller( VOID );

VOID create_can_network_task( VOID );
TaskHandle_t get_can_network_task_handler( VOID );

VOID create_can_irq_task( VOID );
TaskHandle_t get_can_irq_task_handler( VOID );

VOID create_can_rx_task( VOID );
TaskHandle_t get_can_rx_task_handler( VOID );

VOID create_can_tx_task( VOID );
TaskHandle_t get_can_tx_task_handler( VOID );


#endif /* APPL_TASK_H */
