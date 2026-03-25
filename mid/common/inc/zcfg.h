/**
  **************************************************************************************************
  * @file   zcfg.h
  * @brief  Starting point of this project.
  * @by     phucdh141 | 31-Dec-2024 | Launch for FWCore.
  **************************************************************************************************
  * This file is part of FWCore.
  **************************************************************************************************
  */
/*  Indent using spaces
    Tab width   : 4 spaces
    Line width  : 100 characters
    Line ending : LF (0x0A) */

#ifndef _ZCFG_H
#define _ZCFG_H

#ifdef __cplusplus
extern "C" {
#endif

/* ---------------------------------------
    ---------- Error trace options --------
    --------------------------------------- */
/* WERROR==1: Enable printing error messages.
Only recommended during the development or testing phases. */
#if defined (NDEBUG)
    #define ZERROR                      0u  /* Disable in Release mode, DON'T EDIT. */
#else
    /* Enable or disable printing error messages globally. */
    #define ZERROR                      1u  /* 1: Enable, 0: Disable. */
#endif /* NDEBUG */
#if !ZERROR
    #undef ZERROR
#endif

/* ---------------------------------------
    ---------- Debug trace options --------
    --------------------------------------- */
/* ZDEBUG==1: Enable printing debug messages.
Only recommended during the development or testing phases. */
#if defined (NDEBUG)
    #define ZDEBUG                      0u  /* Disable in Release mode, DON'T EDIT. */
#else
    /* Enable or disable printing debug messages globally. */
    #define ZDEBUG                      1u  /* 1: Enable, 0: Disable. */
#endif /* NDEBUG */
#if !ZDEBUG
    #undef VDEBUG
#endif

#if defined (ZERROR) || defined (ZDEBUG)
    /* Enable or disable printing (error and debug) messages in each module. */
    #define TR_APP                     	ZTRACE_ON            /* ZTRACE_ON or ZTRACE_OFF */
	#define TR_HEAP                     ZTRACE_ON            /* ZTRACE_ON or ZTRACE_OFF */
	#define TR_DELAY_BSP				ZTRACE_OFF            /* ZTRACE_ON or ZTRACE_OFF */
	#define TR_DELAY					ZTRACE_OFF            /* ZTRACE_ON or ZTRACE_OFF */
	#define TR_LCD1602_BSP				ZTRACE_ON			/* ZTRACE_ON or ZTRACE_OFF */
	#define TR_LCD1602					ZTRACE_ON			/* ZTRACE_ON or ZTRACE_OFF */
	#define TR_NTC_BSP					ZTRACE_ON			/* ZTRACE_ON or ZTRACE_OFF */
	#define TR_NTC						ZTRACE_ON			/* ZTRACE_ON or ZTRACE_OFF */
	#define TR_STEP_MOTOR				ZTRACE_ON			/* ZTRACE_ON or ZTRACE_OFF */
	#define TR_COMM_BSP					ZTRACE_ON			/* ZTRACE_ON or ZTRACE_OFF */
	#define TR_COMM						ZTRACE_ON			/* ZTRACE_ON or ZTRACE_OFF */
	#define TR_DC_MOTOR					ZTRACE_ON			/* ZTRACE_ON or ZTRACE_OFF */
	#define TR_DC_MOTOR_BSP				ZTRACE_ON			/* ZTRACE_ON or ZTRACE_OFF */

#endif /* defined(VERROR) || defined(VDEBUG) */

/* ---------------------------------------
    ---------- Assertion trace options ----
    --------------------------------------- */
/* WASSERT==1: Enable FreeRTOS assert facility.
To check how the application is using FreeRTOS. It is highly recommended to develop FreeRTOS
applications with WASSERT enabled.
Only recommended during the development or testing phases. */
#if defined (NDEBUG)
    #define ZASSERT                     0u   /* Disable in Release mode, DON'T EDIT. */
#else
    #define ZASSERT                     1u
#endif /* NDEBUG */
#if !ZASSERT
    #undef ZASSERT
#endif

/* ---------------------------------------
    ------------ Common headers -----------
    --------------------------------------- */

/* Error handling. */
#include "zerr.h"

/* C standard library. */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdarg.h>
#include <math.h>

/* RTOS. */
#include "cmsis_os.h"

/* Middleware. */
#include "ztrace.h"

/* ---------------------------------------
    -------- Task priority options --------
    --------------------------------------- */

#define ZAPP_PRIO_START             		(tskIDLE_PRIORITY + 2u)
#define ZAPP_PRIO_COMM             			(tskIDLE_PRIORITY + 4u)

/* IDLE task has the lowest priority (priority = 0) in the system. */

/* ---------------------------------------
    ------- Task stack deep options -------
    --------------------------------------- */

#define ZAPP_STACK_DEEP_START           (configMINIMAL_STACK_SIZE * 2u)
#define ZAPP_STACK_DEEP_COMM            (configMINIMAL_STACK_SIZE * 1u)

/* ---------------------------------------
    --------- HW priority options ---------
    --------------------------------------- */
/*
    * Any interrupt that uses RTOS API functions MUST have its priority set to a value that is
    * numerically equal to or greater than the configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY. This
    * ensures the interrupt's logical priority is equal to or less than the
    * configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY
    */

#define HW_PRIO_COMM           		(configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY + 4)

#define HW_PRIO_DELAY_TIM           (configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY + 2)
#define HW_PRIO_DC_MOTOR_TIM        (configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY + 2)

#define HW_PRIO_LOG_UART           	(configLIBRARY_LOWEST_INTERRUPT_PRIORITY)


#ifdef __cplusplus
}
#endif

#endif /* _ZCFG_H */

/* END OF FILE ************************************************************************************/
