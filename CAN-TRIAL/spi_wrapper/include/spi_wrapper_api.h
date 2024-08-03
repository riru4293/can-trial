#ifndef SPI_WRAPPER_API_H
#define SPI_WRAPPER_API_H

#include "app_comdef_type.h"

VOID spiwrp_init();
VOID spiwrp_begin();
VOID spiwrp_end();
BOOL spiwrp_is_busy();
VOID spiwrp_read_array( const size_t n, UCHAR *buf );
VOID spiwrp_write_array( const size_t n, const UCHAR const *buf );
VOID spiwrp_write( const UCHAR val );

#endif /* SPI_WRAPPER_API_H */
