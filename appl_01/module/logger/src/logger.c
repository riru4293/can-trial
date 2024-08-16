/* -------------------------------------------------------------------------- */
/* Includes                                                                   */
/* -------------------------------------------------------------------------- */
/* System */
#include <stdio.h>
#include <string.h>

/* PICO-SDK */
#include "pico/stdlib.h"

/* FreeRTOS */
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>

/* APPL */
#include "public/logger.h"


/* -------------------------------------------------------------------------- */
/* Definitions                                                                */
/* -------------------------------------------------------------------------- */
#define MAXOF_QUEUE_ITEMS   ( (UINT8)100U )
#define SIZEOF_MSG_BUFF     ( (UINT8)( LOG_MAXOF_MSG_LEN + 1U ) )
#define WAITOF_QUEUE_SET    ( (UINT8)0U )


/* -------------------------------------------------------------------------- */
/* Prototypes                                                                 */
/* -------------------------------------------------------------------------- */
static VOID task( VOID *unused );


/* -------------------------------------------------------------------------- */
/* Globals                                                                 */
/* -------------------------------------------------------------------------- */
static volatile QueueHandle_t queue_handle = NULL;
static TaskHandle_t task_handle = NULL;


/* -------------------------------------------------------------------------- */
/* Public functions                                                           */
/* -------------------------------------------------------------------------- */
TaskHandle_t log_get_task_handler( VOID )
{
    return task_handle;
}


VOID log_create_task( VOID )
{
    BaseType_t result;

    /* Create log queue */
    queue_handle = xQueueCreate( MAXOF_QUEUE_ITEMS, SIZEOF_MSG_BUFF );

    if( NULL == queue_handle )
    {
        printf("Failed create a queue for logger.\n");
    }

    /* Create logger task */
    result = xTaskCreate( task, "LOGGER_TASK", 1024, NULL, 1, &task_handle );

    if( pdPASS != result )
    {
        printf("Failed create a logger task.\n");
    }
}


VOID log_put_msg( const UINT8 n, const UINT8 *msg )
{
    BaseType_t result;
    UINT8 buf[ SIZEOF_MSG_BUFF ] = { 0U };

    if( ( LOG_MINOF_MSG_LEN <= n ) && ( LOG_MAXOF_MSG_LEN >= n ) )
    {
        /* Set NULL to last character */
        memcpy( buf, msg, n );

        /* Put message to queue */
        result = xQueueSendToBack( queue_handle, buf, WAITOF_QUEUE_SET );

        if( pdPASS != result )
        {
            printf("The logger queue has overflowed.\n");
        }
    }
}


/* -------------------------------------------------------------------------- */
/* Private functions                                                          */
/* -------------------------------------------------------------------------- */
static VOID task( VOID *unused )
{
    BaseType_t result;
    UINT8 msg[ SIZEOF_MSG_BUFF ] = { 0U };

    while( TRUE )
    {
        /* Wait a log message */
        result = xQueueReceive( queue_handle, msg, portMAX_DELAY );

        /* Output a message */
        if ( pdPASS == result )
        {
            printf("%s\n", msg );
        }
    }
}
