#ifndef LOGGER_API_H
#define LOGGER_API_H

#define LG_MINOF_MSG_LEN ( (UCHAR)1U )
#define LG_MAXOF_MSG_LEN ( (UCHAR)40U )

#include "logger_result.h"

lg_result_t lg_init( VOID );
lg_result_t lg_put_msg( const UCHAR n, const UCHAR* msg );
VOID lg_logger_task(VOID* unused_arg);

#endif /* LOGGER_API_H */
