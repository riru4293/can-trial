#ifndef RP2040_H
#define RP2040_H


#include "public/driver.h"


drv_result_t init_stdio( VOID );
VOID init_led( VOID );
VOID init_spi( VOID );
VOID turn_on_led( VOID );
VOID turn_off_led( VOID );
VOID begin_spi( VOID );
VOID end_spi( VOID );
VOID read_array_spi( const size_t n, UINT8 *buf );
VOID write_array_spi( const size_t n, const UINT8 const *buf );
VOID write_spi( const UINT8 val );

#endif /* RP2040_H */
