#ifndef DRIVER_H
#define DRIVER_H


#include "appl_common.h"


typedef UINT8 drv_result_t;
typedef VOID (*drv_irq_callback_t)( UINT gpio, UINT32 event_mask );

#define DRV_SUCCESS ( (UINT8)0x00U )
#define DRV_FAILURE ( (UINT8)0xFFU )


drv_result_t drv_init( VOID );
VOID drv_turn_on_internal_led( VOID );
VOID drv_turn_off_internal_led( VOID );
VOID drv_begin_spi( VOID );
VOID drv_end_spi( VOID );
VOID drv_read_array_spi( const size_t n, UINT8 *buf );
VOID drv_write_array_spi( const size_t n, const UINT8 const *buf );
VOID drv_write_spi( const UINT8 val );

VOID drv_set_irq_callback( drv_irq_callback_t callback );
VOID drv_enable_irq( BOOL enabled );


#endif /* DRIVER_H */
