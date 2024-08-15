#ifndef LOGGER_H
#define LOGGER_H


#include "appl_common.h"


typedef UINT8 log_result_t;


#define LOG_SUCCESS ( (UINT8)0x00U )
#define LOG_FAILURE ( (UINT8)0xFFU )

#define LOG_MINOF_MSG_LEN ( (UINT8)1U )
#define LOG_MAXOF_MSG_LEN ( (UINT8)40U )


log_result_t log_create_task( VOID );
log_result_t log_put_msg( const UINT8 n, const UINT8* msg );


#endif /* LOGGER_H */
