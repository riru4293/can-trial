#ifndef APPL_COMMON_H
#define APPL_COMMON_H

/* -------------------------------------------------------------------------- */
/* Type definition                                                            */
/* -------------------------------------------------------------------------- */
typedef uint     UINT;      /* 32bit */
typedef uint8_t  UINT8;
typedef uint16_t UINT16;
typedef uint32_t UINT32;
typedef uint64_t UINT64;

typedef bool BOOL;
typedef void VOID;
typedef UINT8 result_t;

#endif /* APPL_COMMON_H */

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

#define MAXOF_UINT      ( (UINT)0xFFFFFFFFU )
#define MAXOF_UINT8     ( (UINT8)0xFFU )
#define MAXOF_UINT16    ( (UINT16)0xFFFFU )
#define MAXOF_UINT32    ( (UINT32)0xFFFFFFFFU )
#define MAXOF_UINT64    ( (UINT64)0xFFFFFFFFFFFFFFFFULL )

#define APPL_SUCCESS    ( (result_t)0x00U )
#define APPL_FAILURE    ( (result_t)0xFFU )

#define WAIT_NONE       ( (TickType_t)0U )
#define WAIT_FOREVER    ( (TickType_t)portMAX_DELAY )
