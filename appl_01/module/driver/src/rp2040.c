#include "hardware/spi.h"
#include "private/rp2040.h"


#define GPIO_NUM_SPI_1_MISO             ( (UCHAR) 4U )
#define GPIO_NUM_SPI_1_CS               ( (UCHAR) 5U )
#define GPIO_NUM_SPI_1_SCK              ( (UCHAR) 6U )
#define GPIO_NUM_SPI_1_MOSI             ( (UCHAR) 7U )
#define GPIO_NUM_CAN_INTERRUPTION       ( (UCHAR)22U )
#define GPIO_NUM_INTERNAL_LED           ( (UCHAR)25U )

#define SPI_BAUDRATE_10MHZ              ( (UINT)10000000U ) /* 10MHz */
#define SPI_REPEATED_TX_DATA            ( (UCHAR)0U )


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


VOID read_array_spi( const size_t n, UCHAR *buf )
{
    (VOID)spi_read_blocking( spi0, SPI_REPEATED_TX_DATA, buf, n );
}


VOID write_array_spi( const size_t n, const UCHAR const *buf )
{
    (VOID)spi_write_blocking( spi0, buf, n );
}