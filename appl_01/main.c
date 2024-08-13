/**
 * CAN communication trial
 * 
 * @copyright 2024, riru
 * @version   0.0.2
 * @licence   BSD-2-Clause
 */
#include "appl_common.h"
#include "driver/include/public/driver.h"
#include "logger/include/public/logger.h"
#include "main.h"

/*
 * GLOBALS
 */

/*
 * FUNCTIONS
 */


/*
 * RUNTIME START
 */
int main()
{
    drv_result_t result;

    result = drv_init();

    // if( ( BD_SUCCESS == result_bd_init ) && ( LG_SUCCESS == result_lg_init ) )
    if( ( DRV_SUCCESS == result ) )
    {
        // Print the application information to UART.
        printf("App: %s %s.\n", APP_NAME, APP_VERSION);
    }

    temp_init();

    xTaskCreate(temp_task, "TEMP_TASK", 1288, NULL, 2, NULL);
    log_create_task();

    vTaskStartScheduler();
    
    // We should never get here, but just in case...
    while(true) {
        // NOP
    };
}
