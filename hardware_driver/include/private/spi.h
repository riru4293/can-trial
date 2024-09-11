#ifndef SPI_H
#define SPI_H

/* -------------------------------------------------------------------------- */
/* Include                                                                    */
/* -------------------------------------------------------------------------- */
#include <my_types.h>

VOID begin_spi_1_communication( VOID );
VOID end_sspi_1_communication( VOID );
VOID begin_spi_1_communication( VOID );
VOID end_spi_1_communication( VOID );
VOID read_spi_1_array( const SIZE_T len, UINT8 *buff );
VOID write_spi_1_array( const SIZE_T len, const UINT8 const *buff );
VOID read_spi_1( VOID );
VOID write_spi_1( const UINT8 val );

// static VOID read_sspi_1_array( const SIZE_T len, UINT8 *buff )
// {
//     if( ( 0U < len ) && ( NULL != buff ) )
//     {
//         (VOID)spi_read_blocking( SSPI_1_HW, SPI_REPEATED_TX_DATA, buff, len );
//     }
// }

// static VOID write_sspi_1_array( const SIZE_T len, const UINT8 const *buff )
// {
//     if( ( 0U < len ) && ( NULL != buff ) )
//     {
//         (VOID)spi_write_blocking( SSPI_1_HW, buff, len );
//     }
// }

// static VOID read_sspi_1( VOID )
// {
//     UINT8 val;

//     read_sspi_1_array( sizeof( UINT8 ), &val );

//     return val;
// }

// static VOID write_sspi_1( const UINT8 val )
// {
//     write_sspi_1_array( sizeof( UINT8 ), &val );
// }

#endif /* SPI_H */