/**
 * CAN communication trial
 * 
 * @copyright 2024, riru
 * @version   0.0.2
 * @licence   BSD-2-Clause
 */
#include "appl_common.h"
#include "board_driver/include/public/board_driver_api.h"
#include "logger/include/public/logger_api.h"
#include "main.h"

/*
 * GLOBALS
 */
TaskHandle_t temp_task_handle = NULL;
TaskHandle_t logger_task_handle = NULL;

/*
 * FUNCTIONS
 */


/*
 * RUNTIME START
 */
int main()
{
    bd_result_t result_bd_init;
    lg_result_t result_lg_init;

    result_bd_init = bd_init();
    result_lg_init = lg_init();

    if( ( BD_SUCCESS == result_bd_init ) && ( LG_SUCCESS == result_lg_init ) )
    {
        // Print the application information to UART.
        printf("App: %s %s.\n", APP_NAME, APP_VERSION);
    }

    temp_init();

    xTaskCreate(temp_task, "TEMP_TASK", 1288, NULL, 5, &temp_task_handle);
    xTaskCreate(lg_logger_task, "LOGGER_TASK", 1288, NULL, 1, &logger_task_handle);

    vTaskStartScheduler();
    
    // We should never get here, but just in case...
    while(true) {
        // NOP
    };
}
