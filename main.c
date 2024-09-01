/* -------------------------------------------------------------------------- */
/* Include                                                                    */
/* -------------------------------------------------------------------------- */
/* System */
#include <stdio.h>

/* RP2040 */
#include <pico/stdlib.h>

/* FreeRTOS */
#include <FreeRTOS.h>
#include <task.h>
#include <timers.h>
#include <semphr.h>
#include <event_groups.h>
#include <queue.h>


/* -------------------------------------------------------------------------- */
/* Type definition                                                            */
/* -------------------------------------------------------------------------- */
typedef uint     UINT;      /* 32bit */
typedef uint8_t  UINT8;
typedef uint16_t UINT16;
typedef uint32_t UINT32;
typedef uint64_t UINT64;

typedef bool BOOL;
typedef void VOID;
typedef UINT8 result_t;


/* -------------------------------------------------------------------------- */
/* Macro                                                                      */
/* -------------------------------------------------------------------------- */
#define TRUE            ( (BOOL)true )
#define FALSE           ( (BOOL)false )

#define MINOF_UINT      ( (UINT)0U )
#define MINOF_UINT8     ( (UINT8)0U )
#define MINOF_UINT16    ( (UINT16)0U )
#define MINOF_UINT32    ( (UINT32)0U )
#define MINOF_UINT64    ( (UINT64)0U )

#define MAXOF_UINT      ( (UINT)0xFFFFFFFFU )
#define MAXOF_UINT8     ( (UINT8)0xFFU )
#define MAXOF_UINT16    ( (UINT16)0xFFFFU )
#define MAXOF_UINT32    ( (UINT32)0xFFFFFFFFU )
#define MAXOF_UINT64    ( (UINT64)0xFFFFFFFFFFFFFFFFULL )

#define APPL_SUCCESS    ( (result_t)0x00U )
#define APPL_FAILURE    ( (result_t)0xFFU )

#define WAIT_NONE       ( (TickType_t)0U )
#define WAIT_FOREVER    ( (TickType_t)portMAX_DELAY )


/* -------------------------------------------------------------------------- */
/* Prototype                                                                  */
/* -------------------------------------------------------------------------- */
static VOID task( VOID* unused );
static VOID task2( VOID* unused );
result_t request_begin_communication( VOID );
result_t request_end_communication( VOID );

/* -------------------------------------------------------------------------- */
/* Global                                                                     */
/* -------------------------------------------------------------------------- */
volatile static SemaphoreHandle_t g_semaphore;
static TaskHandle_t g_network_manager_task_handle = NULL;
static TaskHandle_t g_can_tx_task_handle = NULL;
static EventGroupHandle_t g_network_manager_event_handle;
static EventGroupHandle_t g_can_tx_event_handle;
static TimerHandle_t g_timer_handle;
static VOID timer_callback( TimerHandle_t timer_handler );
static BaseType_t xTimer2Started;
static volatile QueueHandle_t g_queue_handle = NULL;
static const UINT8 g_ending_communication = 0x00;
static const UINT8 g_beginning_communication = 0x01;


/* -------------------------------------------------------------------------- */
/* Public function                                                            */
/* -------------------------------------------------------------------------- */
int main()
{
    stdio_init_all();

    g_network_manager_event_handle = xEventGroupCreate();
    g_can_tx_event_handle = xEventGroupCreate();

    /* Create log queue */
    g_queue_handle = xQueueCreate( 1, 1 );

    xTaskCreate( task, "NET_MGR", 1024, NULL, 1, &g_network_manager_task_handle );
    xTaskCreate( task2, "CAN_TX", 1024, NULL, 2, &g_can_tx_task_handle );

    vTaskStartScheduler();

    while (true) {
        // NOP
    }
}

/*
 * CAN通信の開始を要求する
 *
 * args:    nothing
 * return:  APPL_SUCCESS    要求を受け付けた
 *          APPL_FAILURE    要求を拒否した
 * note:    CAN通信の開始もしくは終了を要求中は、要求を拒否する。
 */
result_t request_begin_communication( VOID )
{
    BaseType_t result;

    result = xQueueSendToBack( g_queue_handle, &g_beginning_communication, WAIT_NONE );

    return (pdPASS == result) ? APPL_SUCCESS : APPL_FAILURE;
}

/*
 * CAN通信の終了を要求する
 *
 * args:    nothing
 * return:  APPL_SUCCESS    要求を受け付けた
 *          APPL_FAILURE    要求を拒否した
 * note:    CAN通信の開始もしくは終了を要求中は、要求を拒否する。
 */
result_t request_end_communication( VOID )
{
    BaseType_t result;

    result = xQueueSendToBack( g_queue_handle, &g_ending_communication, WAIT_NONE );

    return (pdPASS == result) ? APPL_SUCCESS : APPL_FAILURE;
}

/* -------------------------------------------------------------------------- */
/* Private function                                                           */
/* -------------------------------------------------------------------------- */
static VOID task( VOID* unused )
{
    BaseType_t result;
    UINT8 request;

    (VOID)request_begin_communication();
    
    while( TRUE )
    {
        /* Wait a begin or end request of communication */
        result = xQueuePeek( g_queue_handle, &request, WAIT_FOREVER );

        switch( request )
        {
        case g_beginning_communication:
            
            // 開始準備要求
            (VOID)xEventGroupSetBits( g_can_tx_event_handle, 0x01U );

            // 準備完了待ち
            (VOID)xEventGroupSync(g_network_manager_event_handle, 0x00U, 0x08U, portMAX_DELAY);

            printf("Begin communication");

            // Wait
            vTaskDelay(1000U);

            printf(" --> Done\n");

            // 処理終了通知
            (VOID)xEventGroupSetBits( g_network_manager_event_handle, 0x04U );
            
            break;
        case g_ending_communication:
        default:
            // 終了準備要求
            (VOID)xEventGroupSetBits( g_can_tx_event_handle, 0x01U );

            // 準備完了待ち
            (VOID)xEventGroupSync(g_network_manager_event_handle, 0x00U, 0x08U, portMAX_DELAY);

            printf("End communication");

            // Wait
            vTaskDelay(3000U);

            printf(" --> Done\n");

            // 処理終了通知
            (VOID)xEventGroupSetBits( g_network_manager_event_handle, 0x04U );

            break;
        }

        do
        {
            result = xQueueReceive( g_queue_handle, &request, WAIT_NONE );
        } while (pdPASS == result);

        switch( request )
        {
        case g_beginning_communication:
            (VOID)request_end_communication();
            break;
        case g_ending_communication:
        default:
            (VOID)request_begin_communication();
            break;
        }
    }
}

static VOID task2( VOID* unused )
{
    EventGroupHandle_t my_hndl = g_can_tx_event_handle;
    EventGroupHandle_t mngr_hndl = g_network_manager_event_handle;
    EventBits_t events;
    
    while( TRUE )
    {
        events = xEventGroupWaitBits( my_hndl, 0x01U, pdTRUE, pdFALSE, WAIT_NONE );

        if(0x00 != (events & 0x01)) // 初期化要求
        {
            // 準備の代わり
            vTaskDelay(500U);

            // 準備完了を応答
            (VOID)xEventGroupSetBits( mngr_hndl, 0x08U );

            // 終了を待つ
            (VOID)xEventGroupSync(mngr_hndl, 0x00U, 0x04U, portMAX_DELAY);

            // 他の作業はしない
            continue;
        }
        else
        {
            vTaskDelay(500U);
            printf("CAN TX work\n");
        }

        printf("CAN TX work\n");
        vTaskDelay(500U);
}
