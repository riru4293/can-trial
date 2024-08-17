#include "hardware/spi.h"
#include "private/rp2040.h"


#define GPIO_VOLT_LOW   ( (BOOL)false   )
#define GPIO_VOLT_HIGH  ( (BOOL)true    )

#define GPIO_NUM_SPI_1_MISO             ( (UINT) 4U )
#define GPIO_NUM_SPI_1_CS               ( (UINT) 5U )
#define GPIO_NUM_SPI_1_SCK              ( (UINT) 6U )
#define GPIO_NUM_SPI_1_MOSI             ( (UINT) 7U )
#define GPIO_NUM_CAN_INTERRUPTION       ( (UINT)21U )
#define GPIO_NUM_INTERNAL_LED           ( (UINT)25U )

#define SPI_BAUDRATE_10MHZ              ( (UINT)10000000U ) /* 10MHz */
#define SPI_REPEATED_TX_DATA            ( (UINT8)0U )


/* Prototypes */
static VOID drv_gpio_irq_handler( UINT gpio, UINT32 events );
static VOID enable_irq_handling( BOOL enabled );


/* Globals */
static drv_irq_callback_t irq_handler = NULL;


drv_result_t init_stdio( VOID )
{
    BOOL result;

    result = stdio_init_all();

    return ( TRUE == result ) ? DRV_SUCCESS : DRV_FAILURE;
}


VOID init_led( VOID )
{
    gpio_init(GPIO_NUM_INTERNAL_LED);
    gpio_set_dir(GPIO_NUM_INTERNAL_LED, GPIO_OUT);
}


VOID init_spi( VOID )
{
    (VOID)spi_init( spi0, SPI_BAUDRATE_10MHZ );

    gpio_set_function( GPIO_NUM_SPI_1_MISO, GPIO_FUNC_SPI );
    gpio_set_function( GPIO_NUM_SPI_1_MOSI, GPIO_FUNC_SPI );
    gpio_set_function( GPIO_NUM_SPI_1_SCK,  GPIO_FUNC_SPI );
    gpio_init( GPIO_NUM_SPI_1_CS );
    gpio_set_dir( GPIO_NUM_SPI_1_CS, GPIO_OUT );
}


VOID turn_on_led( VOID )
{
    gpio_put( PICO_DEFAULT_LED_PIN, GPIO_VOLT_HIGH );
}


VOID turn_off_led( VOID )
{
    gpio_put( PICO_DEFAULT_LED_PIN, GPIO_VOLT_LOW );
}

VOID begin_spi( VOID )
{
    gpio_put( GPIO_NUM_SPI_1_CS, GPIO_VOLT_LOW );
}


VOID end_spi( VOID )
{
    gpio_put( GPIO_NUM_SPI_1_CS, GPIO_VOLT_HIGH );
}


VOID read_array_spi( const size_t n, UINT8 *buf )
{
    (VOID)spi_read_blocking( spi0, SPI_REPEATED_TX_DATA, buf, n );
}


VOID write_array_spi( const size_t n, const UINT8 const *buf )
{
    (VOID)spi_write_blocking( spi0, buf, n );
}


VOID write_spi( const UINT8 val )
{
    write_array_spi( sizeof( UINT8 ), &val );
}


VOID drv_set_irq_handler( drv_irq_callback_t handler )
{
    irq_handler = handler;
}


VOID drv_enable_irq_handling( VOID )
{
    enable_irq_handling( TRUE );
}


VOID drv_disable_irq_handling( VOID )
{
    enable_irq_handling( FALSE );
}

static VOID drv_gpio_irq_handler( UINT gpio, UINT32 events )
{
    if( ( NULL != irq_handler ) && ( GPIO_NUM_CAN_INTERRUPTION == gpio ) && ( GPIO_IRQ_LEVEL_LOW == events ) )
    {
        irq_handler();
    }
}


/* -------------------------------------------------------------------------- */
/* Private functions                                                          */
/* -------------------------------------------------------------------------- */
static VOID enable_irq_handling( BOOL enabled )
{
    gpio_set_irq_enabled_with_callback( GPIO_NUM_CAN_INTERRUPTION, GPIO_IRQ_LEVEL_LOW, enabled, drv_gpio_irq_handler );
}
