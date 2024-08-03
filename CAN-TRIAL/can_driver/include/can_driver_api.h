/*
 * (c) 2024 Project-K.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef CAN_DRIVER_API_H
#define CAN_DRIVER_API_H


#include "pico/stdlib.h"
#include "app_comdef_type.h"


typedef UCHAR cd_result_t;


#define CD_SUCCESS ( (UCHAR)0x00U )
#define CD_FAILURE ( (UCHAR)0xFFU )

#define CD_OPMODE_NORMAL     ( (UCHAR)0x10U )
#define CD_OPMODE_SLEEP      ( (UCHAR)0x20U )
#define CD_OPMODE_LOOPBACK   ( (UCHAR)0x30U )
#define CD_OPMODE_LISTENONLY ( (UCHAR)0x40U )
#define CD_OPMODE_CONFIG     ( (UCHAR)0x50U )

cd_result_t cd_init( void );
UCHAR cd_get_opmode( void );
cd_result_t cd_set_opmode( const UCHAR next_opmode );
cd_result_t cd_reset( void );


#endif /* CAN_DRIVER_API_H */
