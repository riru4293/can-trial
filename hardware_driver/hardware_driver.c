/* -------------------------------------------------------------------------- */
/* Include                                                                    */
/* -------------------------------------------------------------------------- */
/* RP2040 */
#include <pico/stdlib.h>

/* Driver */
#include <hardware_driver.h>
#include <private/rp2040.h>


VOID hwdrv_init_hardware( VOID )
{
    /* Initialize standard I/O */
    stdio_init_all();

    /* Initialize LED */
    rp2040_init_led_1_hw();

    /* Initialize SPI */
    rp2040_init_spi_1_hw();
}

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
