#include "public/board_driver.h"
#include "private/bd_gpio.h"

bd_result_t bd_init( VOID )
{
    bd_result_t result;
    bd_init_gpio();
    return result;
}
