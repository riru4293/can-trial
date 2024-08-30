#include "public/board_driver/board_driver_api.h"
#include "private/board_driver/bd_gpio.h"

bd_result_t bd_init( VOID )
{
    BOOL result;

    bd_init_gpio();

    result = stdio_init_all();

    return ( TRUE == result ) ? BD_SUCCESS : BD_FAILURE;
}

VOID bd_turn_on_internal_led( VOID )
{
    gpio_put(PICO_DEFAULT_LED_PIN, GPIO_VOLT_HIGH);
}


VOID bd_turn_off_internal_led( VOID )
{
    gpio_put(PICO_DEFAULT_LED_PIN, GPIO_VOLT_LOW);
}
