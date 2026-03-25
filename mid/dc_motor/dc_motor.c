/**
  **************************************************************************************************
  * @file   dc_motor.c
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

/* Global configuration. */
#include "zcfg.h"

/* BSP. */
#include "dc_motor_bsp.h"

/* Private macros --------------------------------------------------------------------------------*/
/* Private data types ----------------------------------------------------------------------------*/

typedef struct {
	uint8_t b_is_open;
} dc_motor_t;

/* Private variables -----------------------------------------------------------------------------*/

static dc_motor_t gh_dc_motor = {0};

/* Private function prototypes -------------------------------------------------------------------*/
/* Public function bodies ------------------------------------------------------------------------*/

zerr_t dc_motor_open(void) {
	zerr_t ret = ZERR_OK;
	ZTRACE_DBG(TR_DC_MOTOR, ("DEBUG: open dc motor driver .. \n"));
	if (1 == gh_dc_motor.b_is_open) {ret = ZERR_OPEN_ALREADY;}
	
	if (ZERR_OK == ret) {
		ret = dc_motor_bsp_open(DC_MOTOR_1);
	}
	
	if (ZERR_OK == ret) {
		gh_dc_motor.b_is_open = 1;
	}
	
	return ret;
}
zerr_t dc_motor_start(dc_motor_type_t type, dc_motor_dir_t dir, uint16_t speed) {
	
	zerr_t ret = ZERR_OK;
	ZTRACE_ERR(TR_DC_MOTOR, ("ERROR: Must open dc motor driver first ..\n"), 
							(1 == gh_dc_motor.b_is_open), ret = ZERR_NOT_OPEN;);
	if (ZERR_OK == ret) {
		
	}
	
}
void dc_motor_set_speed(dc_motor_type_t type, uint16_t speed) {

}
void dc_motor_set_dir(dc_motor_type_t type, dc_motor_dir_t dir) {

}

void dc_motor_stop(dc_motor_type_t type) {

}

uint32_t dc_motor_get_max_freq(dc_motor_type_t type) {
	
}

/* Private function bodies -----------------------------------------------------------------------*/

/* END OF FILE ************************************************************************************/
