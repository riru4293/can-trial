/**
 * CAN communication trial
 * 
 * @copyright 2024, riru
 * @version   0.0.2
 * @licence   BSD-2-Clause
 */
#include "appl_common.h"
#include "board_driver/include/public/board_driver_api.h"
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

    result = bd_init();

    if( BD_SUCCESS == result )
    {
        bd_turn_on_internal_led();
        printf("App: %s %s (%i).\n", APP_NAME, APP_VERSION, BUILD_NUM);
    }


    // We should never get here, but just in case...
    while(true) {
        // NOP
    };
}
