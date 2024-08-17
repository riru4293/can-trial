#ifndef DRIVER_H
#define DRIVER_H


#include "public/appl_common.h"


typedef UINT8 drv_result_t;
typedef VOID (*drv_irq_callback_t)( VOID );
typedef VOID (*drv_request_callback_t)( drv_result_t result );
typedef UINT8 drv_irq_t;
typedef UINT8 drv_err_t;

#define DRV_SUCCESS ( (UINT8)0x00U )
#define DRV_FAILURE ( (UINT8)0xFFU )

#define DRV_IRQ_NONE            ( (drv_irq_t)0x00U )
#define DRV_IRQ_CAN_MSG_ERR     ( (drv_irq_t)0x80U )
#define DRV_IRQ_CAN_CTRL_WAKE   ( (drv_irq_t)0x40U )
#define DRV_IRQ_CAN_CTRL_ERR    ( (drv_irq_t)0x20U )
#define DRV_IRQ_CAN_TX2_EMPTY   ( (drv_irq_t)0x10U )
#define DRV_IRQ_CAN_TX1_EMPTY   ( (drv_irq_t)0x08U )
#define DRV_IRQ_CAN_TX0_EMPTY   ( (drv_irq_t)0x04U )
#define DRV_IRQ_CAN_RX1_FULL    ( (drv_irq_t)0x02U )
#define DRV_IRQ_CAN_RX0_FULL    ( (drv_irq_t)0x01U )
#define DRV_IRQ_ALL             ( (drv_irq_t)0xFFU )

#define DRV_ERR_NONE            ( (drv_err_t)0x00U )
#define DRV_ERR_RX1_OVERFLOW    ( (drv_err_t)0x80U )
#define DRV_ERR_RX0_OVERFLOW    ( (drv_err_t)0x40U )
#define DRV_ERR_BUSOFF          ( (drv_err_t)0x20U )
#define DRV_ERR_TX_PASV_ERR     ( (drv_err_t)0x10U )
#define DRV_ERR_RX_PASV_ERR     ( (drv_err_t)0x08U )
#define DRV_ERR_TX_WARN         ( (drv_err_t)0x04U )
#define DRV_ERR_RX_WARN         ( (drv_err_t)0x02U )
#define DRV_ERR_WARN            ( (drv_err_t)0x01U )
#define DRV_ERR_ALL             ( (drv_err_t)0xFFU )

drv_result_t drv_init( VOID );
VOID drv_turn_on_internal_led( VOID );
VOID drv_turn_off_internal_led( VOID );


#ifdef DEBUG
VOID drv_begin_spi( VOID );
VOID drv_end_spi( VOID );
VOID drv_read_array_spi( const size_t n, UINT8 *buf );
VOID drv_write_array_spi( const size_t n, const UINT8 const *buf );
VOID drv_write_spi( const UINT8 val );
#endif /* DEBUG */

VOID drv_set_irq_callback( drv_irq_callback_t callback );
VOID drv_enable_irq_handling( VOID );
VOID drv_disable_irq_handling( VOID );

drv_irq_t drv_get_occurred_irq( VOID );
VOID drv_clear_occurred_irq( drv_irq_t irq );
VOID drv_disable_irq_factor( drv_irq_t irq );
VOID drv_enable_irq_factor( drv_irq_t irq );

drv_err_t drv_get_occurred_err( VOID );
VOID drv_clear_err_rx0_overflow( drv_err_t err );
VOID drv_clear_err_rx1_overflow( drv_err_t err );

// キューで順次実施。ただし、リセットの後は消し去る。
VOID drv_reset_can_controller( VOID );
drv_result_t drv_request_begin_can_network( drv_request_callback_t handler );
drv_result_t drv_request_end_can_network( drv_request_callback_t handler );

#ifdef DEBUG 
VOID drvtmp_to_normal_mode( VOID );
#endif /* DEBUG */


#endif /* DRIVER_H */
