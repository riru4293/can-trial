#include <public/appl_common.h>
#include <private/board_driver/bd_gpio.h>

#define GPIO_NUM_SPI_1_MISO             ( (UCHAR) 4U )
#define GPIO_NUM_SPI_1_CS               ( (UCHAR) 5U )
#define GPIO_NUM_SPI_1_SCK              ( (UCHAR) 6U )
#define GPIO_NUM_SPI_1_MOSI             ( (UCHAR) 7U )

#define GPIO_NUM_CAN_INTERRUPTION       ( (UCHAR)22U )

#define GPIO_NUM_INTERNAL_LED           ( (UCHAR)25U )

static VOID bd_init_gpio_internal_led( VOID );
static VOID bd_init_gpio_spi_1( VOID );


VOID bd_init_gpio( VOID )
{
    bd_init_gpio_internal_led();
    bd_init_gpio_spi_1();
}


static VOID bd_init_gpio_internal_led( VOID )
{
    gpio_init(GPIO_NUM_INTERNAL_LED);
    gpio_set_dir(GPIO_NUM_INTERNAL_LED, GPIO_OUT);
}


static VOID bd_init_gpio_spi_1( VOID )
{
    gpio_set_function( GPIO_NUM_SPI_1_MISO, GPIO_FUNC_SPI );
    gpio_set_function( GPIO_NUM_SPI_1_MOSI, GPIO_FUNC_SPI );
    gpio_set_function( GPIO_NUM_SPI_1_SCK,  GPIO_FUNC_SPI );
    gpio_init( GPIO_NUM_SPI_1_CS );
    gpio_set_dir( GPIO_NUM_SPI_1_CS, GPIO_OUT );
}


