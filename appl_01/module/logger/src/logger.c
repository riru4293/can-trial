// FreeRTOS
#include <FreeRTOS.h>
// #include <task.h>
#include <queue.h>
#include <stdio.h>
#include <string.h>

#include "public/logger_api.h"

#define MAXOF_QUEUE_ITEMS ( (UCHAR)100U )
#define SIZEOF_MSG_BUFF ( (UCHAR)( LG_MAXOF_MSG_LEN + 1U ) )
#define WAITOF_QUEUE_SET ( (UCHAR)0U )
#define WAITOF_QUEUE_GET ( (UCHAR)0U )

static volatile QueueHandle_t queue = NULL;

VOID lg_logger_task( VOID* unused_arg )
{
    BaseType_t result;
    UCHAR tmp_msg[ SIZEOF_MSG_BUFF ] = { 0U };

    while( TRUE )
    {
        // // Get a log message. When not cause timeout.
        // result = xQueueReceive( queue, tmp_msg, portMAX_DELAY );

        // if ( pdPASS == result )
        // {
        //     printf("%s\n", tmp_msg );
        // }
    }
}

lg_result_t lg_init( VOID )
{
    queue = xQueueCreate( LG_MAXOF_MSG_LEN, MAXOF_QUEUE_ITEMS );

    return ( NULL != queue ) ? LG_SUCCESS : LG_FAILURE;
    // return LG_SUCCESS;
}


lg_result_t lg_put_msg( const UCHAR n, const UCHAR* msg )
{
    BaseType_t result = pdFAIL;
    // UCHAR tmp_msg[ SIZEOF_MSG_BUFF ] = { 0U };

    // if( ( LG_MINOF_MSG_LEN <= n ) && ( LG_MAXOF_MSG_LEN >= n ) )
    // {
    //     // Set NULL to last character
    //     memcpy( tmp_msg, msg, n );

    //     result = xQueueSendToBack( queue, tmp_msg, WAITOF_QUEUE_SET );
    // }

    return ( pdPASS == result ) ? LG_SUCCESS : LG_FAILURE;
}

