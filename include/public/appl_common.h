#ifndef APPL_COMMON_H
#define APPL_COMMON_H

#include <pico/types.h>

/* -------------------------------------------------------------------------- */
/* Type definition                                                            */
/* -------------------------------------------------------------------------- */
typedef uint        UINT;
typedef uint8_t     UINT8;
typedef uint16_t    UINT16;
typedef uint32_t    UINT32;
typedef uint64_t    UINT64;
typedef bool        BOOL;
typedef void        VOID;
typedef UINT8       RESULT_T;
typedef size_t      SIZE_T;

/* -------------------------------------------------------------------------- */
/* Macro                                                                      */
/* -------------------------------------------------------------------------- */
#define TRUE            ( (BOOL)true )
#define FALSE           ( (BOOL)false )

#define MINOF_UINT      ( (UINT)0U )
#define MINOF_UINT8     ( (UINT8)0U )
#define MINOF_UINT16    ( (UINT16)0U )
#define MINOF_UINT32    ( (UINT32)0U )
#define MINOF_UINT64    ( (UINT64)0U )

#define MAXOF_UINT      ( (UINT)UINT_LEAST32_MAX )
#define MAXOF_UINT8     ( (UINT8)UINT_LEAST8_MAX )
#define MAXOF_UINT16    ( (UINT16)UINT_LEAST16_MAX )
#define MAXOF_UINT32    ( (UINT32)UINT_LEAST32_MAX )
#define MAXOF_UINT64    ( (UINT64)UINT_LEAST64_MAX )

#define APPL_SUCCESS    ( (RESULT_T)0x00U )
#define APPL_FAILURE    ( (RESULT_T)0xFFU )

#define WAIT_NONE       ( (TickType_t)0U )
#define WAIT_FOREVER    ( (TickType_t)portMAX_DELAY )

#endif /* APPL_COMMON_H */