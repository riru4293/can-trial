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


/* -------------------------------------------------------------------------- */
/* Prototypes                                                                 */
/* -------------------------------------------------------------------------- */
VOID create_init_task( VOID );
TaskHandle_t get_init_task_handler( VOID );

VOID create_irq_task( VOID );
TaskHandle_t get_irq_task_handler( VOID );

VOID create_can_rx_task( VOID );
TaskHandle_t get_can_rx_task_handler( VOID );

VOID create_can_tx_task( VOID );
TaskHandle_t get_can_tx_task_handler( VOID );


#endif /* APPL_TASK_H */
