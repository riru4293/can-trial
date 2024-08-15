#include <stdio.h>
#include <string.h>

// FreeRTOS
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>

#include "public/logger.h"

#define MAXOF_QUEUE_ITEMS ( (UINT8)100U )
#define SIZEOF_MSG_BUFF ( (UINT8)( LOG_MAXOF_MSG_LEN + 1U ) )
#define WAITOF_QUEUE_SET ( (UINT8)0U )
#define WAITOF_QUEUE_GET ( (UINT8)0U )

static volatile QueueHandle_t queue = NULL;
static VOID task( VOID* unused_arg );

static VOID task( VOID* unused_arg )
{
    BaseType_t result;
    UINT8 tmp_msg[ SIZEOF_MSG_BUFF ] = { 0U };

    while( TRUE )
    {
        // Get a log message. When not cause timeout.
        result = xQueueReceive( queue, tmp_msg, portMAX_DELAY );

        if ( pdPASS == result )
        {
            printf("%s\n", tmp_msg );
        }
    }
}

log_result_t log_create_task( VOID )
{
    queue = xQueueCreate( MAXOF_QUEUE_ITEMS, SIZEOF_MSG_BUFF );

    xTaskCreate( task, "LOGGER_TASK", 1024, NULL, 1, NULL );

    return ( NULL != queue ) ? LOG_SUCCESS : LOG_FAILURE;
}


log_result_t log_put_msg( const UINT8 n, const UINT8* msg )
{
    BaseType_t result = pdFAIL;
    UINT8 tmp_msg[ SIZEOF_MSG_BUFF ] = { 0U };

    if( ( LOG_MINOF_MSG_LEN <= n ) && ( LOG_MAXOF_MSG_LEN >= n ) )
    {
        // Set NULL to last character
        memcpy( tmp_msg, msg, n );

        result = xQueueSendToBack( queue, tmp_msg, WAITOF_QUEUE_SET );
    }

    return ( pdPASS == result ) ? LOG_SUCCESS : LOG_FAILURE;
}

