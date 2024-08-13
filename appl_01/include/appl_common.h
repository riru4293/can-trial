#ifndef APPL_COMMON_H
#define APPL_COMMON_H

#include "pico/stdlib.h"

typedef uint8_t UCHAR;
typedef uint16_t USHORT;
typedef uint32_t UINT;
typedef uint64_t ULONG;
typedef bool BOOL;
typedef void VOID;

#define TRUE            ( (BOOL)true    )
#define FALSE           ( (BOOL)false   )

#define GPIO_VOLT_LOW   ( (BOOL)false   )
#define GPIO_VOLT_HIGH  ( (BOOL)true    )

#endif /* APPL_COMMON_H */
