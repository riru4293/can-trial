#ifndef APPL_TASK_H
#define APPL_TASK_H


/* -------------------------------------------------------------------------- */
/* Includes                                                                   */
/* -------------------------------------------------------------------------- */
/* System */

/* PICO-SDK */

/* FreeRTOS */
#include <task.h>
#include <event_groups.h>

/* APPL */
#include "appl_common.h"


/* -------------------------------------------------------------------------- */
/* Definitions                                                                */
/* -------------------------------------------------------------------------- */
#define MAXOF_TASK_PRIORITY     ( configTIMER_TASK_PRIORITY - 1 )
#define CAN_INIT_TASK_PRIORITY  ( MAXOF_TASK_PRIORITY )
#define CAN_IRQ_TASK_PRIORITY   ( CAN_INIT_TASK_PRIORITY - 1 )
#define CAN_RX_TASK_PRIORITY    ( CAN_IRQ_TASK_PRIORITY - 1 )
#define CAN_TX_TASK_PRIORITY    ( CAN_RX_TASK_PRIORITY - 1 )

/* -------------------------------------------------------------------------- */
/* Prototypes                                                                 */
/* -------------------------------------------------------------------------- */
VOID create_can_init_task( VOID );
TaskHandle_t get_can_init_task_handler( VOID );
VOID request_reset_can_controller( VOID );

VOID create_can_network_task( VOID );
TaskHandle_t get_can_network_task_handler( VOID );

VOID canirq_create_task( VOID );
TaskHandle_t canirq_get_task_handler( VOID );

VOID create_can_rx_task( VOID );
TaskHandle_t get_can_rx_task_handler( VOID );
EventGroupHandle_t canrx_get_event_handle( VOID );


VOID create_can_tx_task( VOID );
TaskHandle_t get_can_tx_task_handler( VOID );
EventGroupHandle_t cantx_get_event_handle( VOID );


#endif /* APPL_TASK_H */
