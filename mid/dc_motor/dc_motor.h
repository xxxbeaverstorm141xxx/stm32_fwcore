/**
  **************************************************************************************************
  * @file   dc_motor.h
  * @brief  Starting point of this project.
  * @by     duonghd | 31-Dec-2024 | Launch for WhiteCat-FWCore.
  **************************************************************************************************
  * This file is part of WhiteCat-FWCore.
  **************************************************************************************************
  */

/*  Indent using spaces
    Tab width   : 4 spaces
    Line width  : 100 characters
    Line ending : LF (0x0A) */

/* Includes --------------------------------------------------------------------------------------*/

#ifndef _DC_MOTOR_H
#define _DC_MOTOR_H

#ifdef __cplusplus
extern "C" {
#endif

/* Global configuration. */
#include "zerr.h"

#include "stm32f1xx_hal.h"

/* Private macros --------------------------------------------------------------------------------*/

typedef enum {
	DC_MOTOR_1=0u,
	DC_MOTOR_2
} dc_motor_type_t;

typedef enum {
	DC_DIR_CW=0u,
	DC_DIR_CCW
} dc_motor_dir_t;
	
/* Private data types ----------------------------------------------------------------------------*/
/* Private variables -----------------------------------------------------------------------------*/
/* Private function prototypes -------------------------------------------------------------------*/
/* Public function bodies ------------------------------------------------------------------------*/

zerr_t dc_motor_open(void);
zerr_t dc_motor_start(dc_motor_type_t type, dc_motor_dir_t dir, uint16_t speed);
void dc_motor_set_speed(dc_motor_type_t type, uint16_t speed);
void dc_motor_set_dir(dc_motor_type_t type, dc_motor_dir_t dir);
void dc_motor_stop(dc_motor_type_t type);
uint32_t dc_motor_get_max_freq(dc_motor_type_t type);

#ifdef __cplusplus
}
#endif

#endif /* _DC_MOTOR_H */

/* Private function bodies -----------------------------------------------------------------------*/

/* END OF FILE ************************************************************************************/
