#include <stdio.h>
#include <string.h>

// FreeRTOS
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>

#include "public/logger.h"

#define MAXOF_QUEUE_ITEMS ( (UCHAR)10U )
#define SIZEOF_MSG_BUFF ( (UCHAR)( LOG_MAXOF_MSG_LEN + 1U ) )
#define WAITOF_QUEUE_SET ( (UCHAR)0U )
#define WAITOF_QUEUE_GET ( (UCHAR)0U )

static volatile QueueHandle_t queue = NULL;
static VOID task( VOID* unused_arg );

static VOID task( VOID* unused_arg )
{
    BaseType_t result;
    UCHAR tmp_msg[ SIZEOF_MSG_BUFF ] = { 0U };

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
    queue = xQueueCreate( SIZEOF_MSG_BUFF, MAXOF_QUEUE_ITEMS );

    xTaskCreate( task, "LOGGER_TASK", 1200, NULL, 1, NULL );

    return ( NULL != queue ) ? LOG_SUCCESS : LOG_FAILURE;
}


log_result_t log_put_msg( const UCHAR n, const UCHAR* msg )
{
    BaseType_t result = pdFAIL;
    UCHAR tmp_msg[ SIZEOF_MSG_BUFF ] = { 0U };

    if( ( LOG_MINOF_MSG_LEN <= n ) && ( LOG_MAXOF_MSG_LEN >= n ) )
    {
        // Set NULL to last character
        memcpy( tmp_msg, msg, n );

        result = xQueueSendToBack( queue, tmp_msg, WAITOF_QUEUE_SET );
    }

    return ( pdPASS == result ) ? LOG_SUCCESS : LOG_FAILURE;
}

