#ifndef DRIVER_H
#define DRIVER_H


#include "public/appl_common.h"


typedef UINT8 drv_result_t;
typedef VOID (*drv_irq_callback_t)( VOID );

#define DRV_SUCCESS ( (UINT8)0x00U )
#define DRV_FAILURE ( (UINT8)0xFFU )

#define DRV_IRQ_NONE            ( (UINT8)0x00U )
#define DRV_IRQ_CAN_MSG_ERR     ( (UINT8)0x80U )
#define DRV_IRQ_CAN_CTRL_WAKE   ( (UINT8)0x40U )
#define DRV_IRQ_CAN_CTRL_ERR    ( (UINT8)0x20U )
#define DRV_IRQ_CAN_TX2_EMPTY   ( (UINT8)0x10U )
#define DRV_IRQ_CAN_TX1_EMPTY   ( (UINT8)0x08U )
#define DRV_IRQ_CAN_TX0_EMPTY   ( (UINT8)0x04U )
#define DRV_IRQ_CAN_RX1_FULL    ( (UINT8)0x02U )
#define DRV_IRQ_CAN_RX0_FULL    ( (UINT8)0x01U )
#define DRV_IRQ_ALL             ( (UINT8)0xFFU )

drv_result_t drv_init( VOID );
VOID drv_turn_on_internal_led( VOID );
VOID drv_turn_off_internal_led( VOID );
VOID drv_begin_spi( VOID );
VOID drv_end_spi( VOID );
VOID drv_read_array_spi( const size_t n, UINT8 *buf );
VOID drv_write_array_spi( const size_t n, const UINT8 const *buf );
VOID drv_write_spi( const UINT8 val );

VOID drv_set_irq_callback( drv_irq_callback_t callback );
VOID drv_enable_irq( BOOL enabled );

UINT8 drv_get_occurred_irq( VOID );
VOID drv_clear_occurred_irq( UINT8 sources );
VOID drv_disable_irq_sources( UINT8 sources );
VOID drv_enable_irq_sources( UINT8 sources );

#ifdef DEBUG
UINT8 drvtmp_get_eflg( VOID );
VOID drvtmp_to_normal_mode( VOID );
#endif /* DEBUG */


#endif /* DRIVER_H */
