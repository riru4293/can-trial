#include "public/driver.h"
#include "private/rp2040.h"
#include "private/mcp2515.h"


drv_result_t drv_init( VOID )
{
    drv_result_t result;

    init_led();
    init_spi();

    result = init_stdio();
    
    if( DRV_SUCCESS == result )
    {
        result = init_mcp2515();
    }

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


VOID drv_begin_spi( VOID )
{
    begin_spi();
}


VOID drv_end_spi( VOID )
{
    end_spi();
}


VOID drv_read_array_spi( const size_t n, UCHAR *buf )
{
    read_array_spi( n, buf );
}


VOID drv_write_array_spi( const size_t n, const UCHAR const *buf )
{
    write_array_spi( n, buf );
}


VOID drv_write_spi( const UCHAR val )
{
    write_spi( val );
}
