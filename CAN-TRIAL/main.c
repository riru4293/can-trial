/**
 * CAN communication trial
 * 
 * @copyright 2024, riru
 * @version   0.0.2
 * @licence   BSD-2-Clause
 */
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
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    gpio_put(PICO_DEFAULT_LED_PIN, 1);

    (void)stdio_init_all();

    // Log app info
    printf("App: %s %s (%i).\n", APP_NAME, APP_VERSION, BUILD_NUM);

    printf("[Main] Begin initialize.\n");

    printf("[Main] End initialize.\n");

    gpio_put(PICO_DEFAULT_LED_PIN, 0);


    // We should never get here, but just in case...
    while(true) {
        // NOP
    };
}
