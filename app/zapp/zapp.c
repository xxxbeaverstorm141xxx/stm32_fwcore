/**
  **************************************************************************************************
  * @file   zapp.c
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

/* Application. */
#include "zapp.h"

/* Middle. */
#include "delay.h"

/* Private macros --------------------------------------------------------------------------------*/

#define ZAPP_TASK_DELAY				200
#define ZAPP_TIME_LOG				200

#define TEMP_OPEN		40
#define TEMP_CLOSE 		50

/* Private data types ----------------------------------------------------------------------------*/

typedef struct {
	uint8_t b_is_open;
} sys_h_t;

/* Private variables -----------------------------------------------------------------------------*/

static sys_h_t gh_sys = {0};

/* Private function prototypes -------------------------------------------------------------------*/
		
static void
zapp_task (void* p_para);

/* Public function bodies ------------------------------------------------------------------------*/

/**
  * @brief  Starting point of the application.
  * @note   If a FreeRTOS API function is called before the scheduler has been started then
  *         interrupts will deliberately be left disabled, and not re-enable again until the first
  *         task starts to execute. (http://www.freertos.org/FAQHelp.html)
  * @param  None.
  * @retval None.
  */
void
zapp_open (void)
{
	xTaskCreate(zapp_task,         		/* Function that implements the task. */
				"zapp task",            /* Text name for the task. */
				ZAPP_STACK_DEEP_START,  /* Stack deep in words, NOT bytes. */
				NULL,    				/* Parameter passed into the task. */
				ZAPP_PRIO_START,        /* Priority at which the task is created. */
				NULL);              	/* Used to pass out the created task's handle.*/
    return;
}

/* Private function bodies -----------------------------------------------------------------------*/

/**
  * @brief      Initialize peripherals and create tasks relating to them.
  * @param[in]  p_para: not use.
  * @retval     None.
  */
static void
zapp_task (void* p_para)
{
#if defined (ZDEBUG) && (TR_HEAP & ZTRACE_ON)
    UBaseType_t uxHighWaterMark;
#endif
	zerr_t ret = ZERR_OK;
//	char sd_path[4];   		/* SD logical drive path */

#if defined (ZERROR) || defined (ZDEBUG)
    ret = ztrace_open();
    if (ZERR_OK != ret)  /* Can not print here, just turn led on */
    {
        led_on(LED_ERROR);
        vTaskSuspend(NULL);
    }
#endif
	ZTRACE_DBG(TR_HEAP, ("DEBUG: %s: priority: %u, stack deep: %u byte, free RAM: %u byte\n",
			__FUNCTION__, ZAPP_PRIO_START, ZAPP_STACK_DEEP_START,
			xPortGetFreeHeapSize()));

#if defined (ZDEBUG) && (TR_HEAP & ZTRACE_ON)
    /* Inspect our own high water mark on entering the task. */
    uxHighWaterMark = uxTaskGetStackHighWaterMark( NULL );
	(void) uxHighWaterMark;
#endif
	
	ZTRACE_DBG(TR_APP, ("DEBUG: zapp_task: open delay..\n"));
    ret = delay_open();
    ZTRACE_ERR(TR_APP, ("ERROR: zapp_task: fail\n"), (ZERR_OK == ret), vTaskSuspend(NULL););
	
	ret = ZERR_OK;

#if 1

    for(;;) {
		ZTRACE_DBG(TR_APP, ("DEBUG: zapp_task: task running..\n"));
		vTaskDelay(ZAPP_TASK_DELAY / portTICK_PERIOD_MS);
	}
#endif

	vTaskDelete(NULL);
}
