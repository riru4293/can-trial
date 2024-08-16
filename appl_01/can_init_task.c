/* -------------------------------------------------------------------------- */
/* Includes                                                                   */
/* -------------------------------------------------------------------------- */
/* System */

/* PICO-SDK */

/* FreeRTOS */
#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>

/* APPL */
#include "public/appl_task.h"
#include "driver/include/public/driver.h"
#include "logger/include/public/logger.h"


/* -------------------------------------------------------------------------- */
/* Definitions                                                                */
/* -------------------------------------------------------------------------- */
#ifdef DEBUG
#define CANID ( 0x477U )
#define SPICMD_WRITE_TX0_CONTENT        ( 0x41U )
#define SPICMD_READ_REG                 ( 0x03U )
#define SPICMD_WRITE_TX0_ID             ( 0x40U )
#define SPICMD_REQ_TX0                  ( 0x81U )
#define REG_TXB0D0                      ( 0x36U )
#endif

typedef VOID (*create_task_t)( VOID );


/* -------------------------------------------------------------------------- */
/* Prototypes                                                                 */
/* -------------------------------------------------------------------------- */
static VOID task( VOID* unused );
static VOID reset_can_controller( VOID );
static VOID restart_task( TaskHandle_t handle, create_task_t create_task );


/* -------------------------------------------------------------------------- */
/* Globals                                                                 */
/* -------------------------------------------------------------------------- */
volatile static SemaphoreHandle_t semaphore;
static TaskHandle_t task_handle;
#ifdef DEBUG
static UINT8 txhdr[ 5 ] = { CANID >> 3U, (CANID << 5U) & 0xE0U, 0x00U, 0x00U, 0x08U };
static UINT8 txbdy[ 8 ] = { 0x11U, 0x22U, 0x33U, 0x44U, 0x55U, 0x66U, 0x77U, 0x88U };
static UINT8 tmp_buf[ 8 ] = { 0U };
#endif


/* -------------------------------------------------------------------------- */
/* Public functions                                                           */
/* -------------------------------------------------------------------------- */
VOID create_can_init_task( VOID )
{
    xTaskCreate( task, "CAN_INIT_TASK", 1024, NULL, 8, &task_handle );
}


TaskHandle_t get_can_init_task_handler( VOID )
{
    return task_handle;
}


VOID request_reset_can_controller( VOID )
{
    (VOID)xSemaphoreGive( semaphore );
}


/* -------------------------------------------------------------------------- */
/* Private functions                                                          */
/* -------------------------------------------------------------------------- */
static VOID task( VOID* unused )
{
    /* Create binary semaphore for reset CAN controller */
    semaphore = xSemaphoreCreateBinary();

    /* Begin critical section */
    taskENTER_CRITICAL();

    /* Reset CAN controller */
    reset_can_controller();

    /* End critical section */
    taskEXIT_CRITICAL();
    
    while( TRUE )
    {
        /* Wait a reset request */
        xSemaphoreTake( semaphore, portMAX_DELAY );

        /* Begin critical section */
        taskENTER_CRITICAL();

        restart_task( get_can_irq_task_handler(), create_can_irq_task );
        restart_task( get_can_rx_task_handler(), create_can_rx_task );
        restart_task( get_can_tx_task_handler(), create_can_tx_task );
        restart_task( log_get_task_handler(), log_create_task );

        /* Reset CAN controller */
        reset_can_controller();

        /* End critical section */
        taskEXIT_CRITICAL();
    }
}


static VOID reset_can_controller( VOID )
{
    /* Reset CAN controller */
    drv_reset_can_controller();

#ifdef DEBUG
    /* Set Send Message */
    drv_begin_spi();
    drv_write_spi( SPICMD_WRITE_TX0_CONTENT );
    drv_write_array_spi( 8U/*DLC*/, txbdy );
    drv_end_spi();

    drv_begin_spi();
    drv_write_spi( SPICMD_READ_REG );
    drv_write_spi( REG_TXB0D0 );
    drv_read_array_spi( 8U, tmp_buf );
    drv_end_spi();

    /* Set Send CAN ID, DLC */
    drv_begin_spi();
    drv_write_spi( SPICMD_WRITE_TX0_ID );
    drv_write_array_spi( 5U/*Header Size*/, txhdr );
    drv_end_spi();

    /* Request to send. */
    drv_begin_spi();
    drv_write_spi( SPICMD_REQ_TX0 );
    drv_end_spi();
#endif
}


static VOID restart_task( TaskHandle_t handle, create_task_t create_task )
{
    if( NULL != handle )
    {
        vTaskDelete( handle );

        create_task();
    }
}