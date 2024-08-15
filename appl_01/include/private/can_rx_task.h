#ifndef CAN_RX_TASK_H
#define CAN_RX_TASK_H


// FreeRTOS
#include <task.h>

#include "public/appl_common.h"


/* Prototypes */
VOID create_can_rx_task( VOID );
TaskHandle_t get_can_rx_task_handler( VOID );


#endif      // CAN_RX_TASK_H
