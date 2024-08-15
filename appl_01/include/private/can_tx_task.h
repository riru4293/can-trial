#ifndef CAN_TX_TASK_H
#define CAN_TX_TASK_H


// FreeRTOS
#include <task.h>

#include "public/appl_common.h"


/* Prototypes */
VOID create_can_tx_task( VOID );
TaskHandle_t get_can_tx_task_handler( VOID );


#endif      // CAN_TX_TASK_H
