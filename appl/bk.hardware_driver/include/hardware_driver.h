#ifndef HARDWARE_DRIVER_H
#define HARDWARE_DRIVER_H

#include <appl_common.h>

/* -------------------------------------------------------------------------- */
/* Type definition                                                            */
/* -------------------------------------------------------------------------- */
typedef VOID (*hwdrv_irq_callback_t)( VOID );

/* -------------------------------------------------------------------------- */
/* Prototype                                                                  */
/* -------------------------------------------------------------------------- */
VOID hwdrv_init_hardware( VOID );
ERR_CD_T hwdrv_reset_can_controller( VOID );
VOID hwdrv_turn_on_led( VOID );
VOID hwdrv_turn_off_led( VOID );
VOID hwdrv_set_irq_callback( hwdrv_irq_callback_t callback );
VOID hwdrv_enable_can_irq_handling( VOID );
VOID hwdrv_disable_can_irq_handling( VOID );

#endif /* HARDWARE_DRIVER_H */
