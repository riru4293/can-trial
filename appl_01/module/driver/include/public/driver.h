#ifndef DRIVER_H
#define DRIVER_H


#include "appl_common.h"


typedef UCHAR drv_result_t;


#define DRV_SUCCESS ( (UCHAR)0x00U )
#define DRV_FAILURE ( (UCHAR)0xFFU )


drv_result_t drv_init( VOID );
VOID drv_turn_on_internal_led( VOID );
VOID drv_turn_off_internal_led( VOID );
VOID drv_begin_spi( VOID );
VOID drv_end_spi( VOID );
VOID drv_read_array_spi( const size_t n, UCHAR *buf );
VOID drv_write_array_spi( const size_t n, const UCHAR const *buf );
VOID drv_write_spi( const UCHAR val );


#endif /* DRIVER_H */