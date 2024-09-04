/* RP2040 */
#include <hardware/spi.h>
#include <pico/stdlib.h>

/* APPL */
#include <public/hardware_driver.h>

#define SPI_0_HW                ( spi0 )
#define SPI_1_HW                ( spi1 )

#define GPIO_VOLT_LOW           ( FALSE )
#define GPIO_VOLT_HIGH          ( TRUE )

#define GPIO_IDX_SPI_0_MISO     ( (UINT) 4U )
#define GPIO_IDX_SPI_0_CS       ( (UINT) 5U )
#define GPIO_IDX_SPI_0_SCK      ( (UINT) 6U )
#define GPIO_IDX_SPI_0_MOSI     ( (UINT) 7U )
#define GPIO_IDX_CAN_IRQ        ( (UINT)21U )
#define GPIO_IDX_LED            ( (UINT)25U )

/* Maximum configurable SPI clock: 8.928571MHz.                                     */
/* The maximum SPI clock for the MCP2515 is 10MHz, but this is not configurable.    */
/* Because the SPI clock cannot be set to any value other than the division value   */
/* of the RP2040 frequency that 125 MHz.                                            */
#define SPI_0_BAUDRATE          ( (UINT)8928571U )

/* -------------------------------------------------------------------------- */
/* Prototype                                                                  */
/* -------------------------------------------------------------------------- */
static VOID enable_irq_handling( BOOL enabled );
static VOID irq_callback( UINT gpio, UINT32 events );

/* -------------------------------------------------------------------------- */
/* Global                                                                     */
/* -------------------------------------------------------------------------- */
static hwdrv_irq_callback_t g_external_irq_callback = NULL;

/* -------------------------------------------------------------------------- */
/* Public function                                                            */
/* -------------------------------------------------------------------------- */
VOID hwdrv_init_hardware( VOID )
{
    /* Initialize standard I/O */
    stdio_init_all();

    /* Initialize LED */
    gpio_init(GPIO_IDX_LED);
    gpio_set_dir(GPIO_IDX_LED, GPIO_OUT);

    /* == Initialize SPI ===>>> */
    (VOID)spi_init( SPI_0_HW, SPI_0_BAUDRATE );

    gpio_set_function( GPIO_IDX_SPI_0_MISO, GPIO_FUNC_SPI );
    gpio_set_function( GPIO_IDX_SPI_0_MOSI, GPIO_FUNC_SPI );
    gpio_set_function( GPIO_IDX_SPI_0_SCK,  GPIO_FUNC_SPI );

    gpio_init( GPIO_IDX_SPI_0_CS );
    gpio_set_dir( GPIO_IDX_SPI_0_CS, GPIO_OUT );
    /* <<<=== Initialize SPI == */
}

RESULT_T hwdrv_reset_can_controller( VOID )
{
    // Configure CAN IRQ callback
}

VOID hwdrv_turn_on_led( VOID )
{
    gpio_put( GPIO_IDX_LED, GPIO_VOLT_HIGH );
}

VOID hwdrv_turn_off_led( VOID )
{
    gpio_put( GPIO_IDX_LED, GPIO_VOLT_LOW );
}

VOID hwdrv_set_irq_callback( hwdrv_irq_callback_t callback )
{
    g_external_irq_callback = callback;
}

VOID hwdrv_enable_can_irq_handling( VOID )
{
    enable_irq_handling( TRUE );
}

VOID hwdrv_disable_can_irq_handling( VOID )
{
    enable_irq_handling( FALSE );
}

/* -------------------------------------------------------------------------- */
/* Private functions                                                          */
/* -------------------------------------------------------------------------- */
static VOID enable_irq_handling( BOOL enabled )
{
    gpio_set_irq_enabled_with_callback(
        GPIO_IDX_CAN_IRQ, GPIO_IRQ_LEVEL_LOW, enabled, irq_callback );
}

static VOID irq_callback( UINT gpio, UINT32 events )
{
    if( ( NULL != g_external_irq_callback )
        && ( GPIO_IDX_CAN_IRQ == gpio )
        && ( GPIO_IRQ_LEVEL_LOW == events ) )
    {
        g_external_irq_callback();
    }
}
