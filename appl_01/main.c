/**
 * CAN communication trial
 * 
 * @copyright 2024, riru
 * @version   0.0.2
 * @licence   BSD-2-Clause
 */
#include "driver/include/public/driver.h"
#include "logger/include/public/logger.h"

#include "private/main.h"
#include "public/appl_task.h"


/*
 * GLOBALS
 */
extern TaskHandle_t handle_task_alrt;

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
    
    if( ( DRV_SUCCESS == result ) )
    {
        temp_init();

        // Print the application information to UART.
        printf("App: %s %s.\n", APP_NAME, APP_VERSION);
    }

    xTaskCreate(temp_task, "TEMP_TASK", 1024, NULL, 2, NULL);
    // xTaskCreate(temp_task3, "TEMP_TASK3", 1288, NULL, 3, &handle_task_alrt);
    log_create_task();
    create_can_rx_task();
    create_can_tx_task();
    create_irq_task();

    vTaskStartScheduler();
    
    // We should never get here, but just in case...
    while(true) {
        // NOP
    };
}
