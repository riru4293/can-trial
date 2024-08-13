#ifndef LOGGER_H
#define LOGGER_H


#include "appl_common.h"


typedef UCHAR log_result_t;


#define LOG_SUCCESS ( (UCHAR)0x00U )
#define LOG_FAILURE ( (UCHAR)0xFFU )

#define LOG_MINOF_MSG_LEN ( (UCHAR)1U )
#define LOG_MAXOF_MSG_LEN ( (UCHAR)40U )


log_result_t log_create_task( VOID );
log_result_t log_put_msg( const UCHAR n, const UCHAR* msg );


#endif /* LOGGER_H */
