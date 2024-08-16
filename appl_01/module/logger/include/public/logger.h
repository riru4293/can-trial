#ifndef LOGGER_H
#define LOGGER_H


/* -------------------------------------------------------------------------- */
/* Includes                                                                   */
/* -------------------------------------------------------------------------- */
/* System */

/* PICO-SDK */

/* FreeRTOS */
#include <FreeRTOS.h>
#include <task.h>

/* APPL */
#include "public/appl_common.h"


/* -------------------------------------------------------------------------- */
/* Definitions                                                                */
/* -------------------------------------------------------------------------- */
#define LOG_MINOF_MSG_LEN ( (UINT8)1U )
#define LOG_MAXOF_MSG_LEN ( (UINT8)40U )


/* -------------------------------------------------------------------------- */
/* Prototypes                                                                 */
/* -------------------------------------------------------------------------- */
VOID log_create_task( VOID );
TaskHandle_t log_get_task_handler( VOID );
VOID log_put_msg( const UINT8 n, const UINT8 *msg );


#endif /* LOGGER_H */
