#ifndef BOARD_DRIVER_API_H
#define BOARD_DRIVER_API_H

#include "board_driver_result.h"

bd_result_t bd_init( VOID );
VOID bd_turn_on_internal_led( VOID );
VOID bd_turn_off_internal_led( VOID );

#endif /* BOARD_DRIVER_API_H */