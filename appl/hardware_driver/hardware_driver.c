/* APPL */
#include <hardware_driver.h>

VOID hwdrv_init_hardware( VOID )
{}
RESULT_T hwdrv_reset_can_controller( VOID )
{
    return APPL_SUCCESS;
}
VOID hwdrv_turn_on_led( VOID )
{}
VOID hwdrv_turn_off_led( VOID )
{}
VOID hwdrv_set_irq_callback( hwdrv_irq_callback_t callback )
{}
VOID hwdrv_enable_can_irq_handling( VOID )
{}
VOID hwdrv_disable_can_irq_handling( VOID )
{}
