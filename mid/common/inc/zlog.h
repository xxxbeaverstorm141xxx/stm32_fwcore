/**
  **************************************************************************************************
  * @file   zlog.h
  * @brief  Starting point of this project.
  * @by     phucdh141 | 1-Nov-2024 | Launch for FWCore.
  **************************************************************************************************
  * This file is part of FWCore.
  **************************************************************************************************
  */

/*  Indent using spaces
    Tab width   : 4 spaces
    Line width  : 100 characters
    Line ending : LF (0x0A) */

#ifndef _LOG_H
#define _LOG_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes --------------------------------------------------------------------------------------*/

/* Global configuration. */
#include "zerr.h"

/* Public macros ---------------------------------------------------------------------------------*/

/* Public data types -----------------------------------------------------------------------------*/

/* Public function prototypes --------------------------------------------------------------------*/

/**
  * @brief  Initialize zlog module.
  * @param  None.
  * @retval zerr_t.
  */
zerr_t
zlog_open (void);

/**
  * @brief      Push a formatted string to ch queue.
  * @param[in]  p_fmt: pointer to format string.
  * @param[in]  ...: optional arguments.
  * @retval     None.
  */
void
zlog_printf (const signed char* p_fmt, ...);

#ifdef __cplusplus
}
#endif

#endif /* _LOG_H */
/* END OF FILE ************************************************************************************/
