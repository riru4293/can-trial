/**
 * CAN communication trial
 * 
 * @copyright 2024, riru
 * @version   0.0.2
 * @licence   BSD-2-Clause
 */
#include "appl_common.h"
#include "board_driver/include/public/board_driver.h"
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
    bd_result_t result;

    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    gpio_put(PICO_DEFAULT_LED_PIN, GPIO_VOLT_HIGH);

    (void)stdio_init_all();

    // Log app info
    printf("App: %s %s (%i).\n", APP_NAME, APP_VERSION, BUILD_NUM);

    printf("[Main] Begin initialize.\n");

    result = bd_init();

    printf("[Main] End initialize.\n");

    if( BD_SUCCESS == result )
    {
        gpio_put(PICO_DEFAULT_LED_PIN, GPIO_VOLT_LOW);
    }


    // We should never get here, but just in case...
    while(true) {
        // NOP
    };
}
