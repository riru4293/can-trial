#ifndef DRIVER_H
#define DRIVER_H


#include "appl_common.h"


typedef UCHAR drv_result_t;


#define DRV_SUCCESS ( (UCHAR)0x00U )
#define DRV_FAILURE ( (UCHAR)0xFFU )


drv_result_t drv_init( VOID );
VOID drv_turn_on_internal_led( VOID );
VOID drv_turn_off_internal_led( VOID );


#endif /* DRIVER_H */