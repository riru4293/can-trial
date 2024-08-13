#ifndef RP2040_H
#define RP2040_H


#include "public/driver.h"


drv_result_t init_stdio( VOID );
VOID init_led( VOID );
VOID init_spi( VOID );
VOID turn_on_led( VOID );
VOID turn_off_led( VOID );


#endif /* RP2040_H */
