
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "spi_wrapper_api.h"

#define GPIO_NUM_MISO            ( (UCHAR) 4U )
#define GPIO_NUM_CS              ( (UCHAR) 5U )
#define GPIO_NUM_SCK             ( (UCHAR) 6U )
#define GPIO_NUM_MOSI            ( (UCHAR) 7U )

#define PORT_LOW          ( (bool)false )
#define PORT_HIGH         ( (bool)true )

#define SPI_REPEATED_TX_DATA         ( (UCHAR)0U )

#define SPI_BAUDRATE_10MHZ ( (UCHAR)10000000U ) /* 10MHz */

static BOOL g_spiwrp_is_busy = FALSE;

VOID spiwrp_init()
{
    // ToDo: 排他処理

    
    /* Initialize SPI. */
    (VOID)spi_init( spi0, SPI_BAUDRATE_10MHZ );

    /* Configure GPIO. */
    gpio_set_function( GPIO_NUM_MISO, GPIO_FUNC_SPI );
    gpio_set_function( GPIO_NUM_MOSI, GPIO_FUNC_SPI );
    gpio_set_function( GPIO_NUM_SCK,  GPIO_FUNC_SPI );
    gpio_init( GPIO_NUM_CS );
    gpio_set_dir( GPIO_NUM_CS, GPIO_OUT );

    gpio_put( GPIO_NUM_CS, PORT_HIGH );

    g_spiwrp_is_busy = FALSE;
}

BOOL spiwrp_is_busy()
{
    return g_spiwrp_is_busy;
}

VOID spiwrp_begin()
{
    if( FALSE == g_spiwrp_is_busy )
    {
        g_spiwrp_is_busy = TRUE;
        // ToDo: １回だけ開始可能にする。Endでリセット。
        // ToDo: 排他処理にする。Endまで。
        // ToDo: 成功失敗を返す。

        // ToDo: 呼び出し側は成否を返されても困る。よって、この中で無視するかログ出すか。

        gpio_put( GPIO_NUM_CS, PORT_LOW );
    }
}

VOID spiwrp_end()
{
    if( TRUE == g_spiwrp_is_busy )
    {
        g_spiwrp_is_busy = FALSE;
        gpio_put( GPIO_NUM_CS, PORT_HIGH );
    }
}

VOID spiwrp_read_array( const size_t n, UCHAR *buf )
{
    // ToDo: 不正引数は無視
    (VOID)spi_read_blocking( spi0, SPI_REPEATED_TX_DATA, buf, n );
}

VOID spiwrp_write_array( const size_t n, const UCHAR const *buf )
{
    // ToDo: 不正引数は無視
    (VOID)spi_write_blocking( spi0, buf, n );
}

VOID spiwrp_write( const UCHAR val )
{
    // ToDo: 不正引数は無視
    spiwrp_write_array( sizeof( UCHAR ), &val );
}
