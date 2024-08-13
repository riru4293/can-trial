#include "public/driver.h"
#include "private/rp2040.h"


drv_result_t drv_init( VOID )
{
    drv_result_t result;

    result = init_stdio();
    init_led();
    init_spi();

    return result;
}


VOID drv_turn_on_internal_led( VOID )
{
    turn_on_led();
}


VOID drv_turn_off_internal_led( VOID )
{
    turn_off_led();
}
