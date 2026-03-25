/**
  **************************************************************************************************
  * @file   log_bsp.c
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

/* Includes --------------------------------------------------------------------------------------*/

/* Global configuration. */
#include "zcfg.h"

/* Middleware. */

/* BSP. */
#include "zlog_bsp.h"

/* ST driver. */
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_dma.h"
#include "stm32f1xx_hal_uart.h"

/* Private data types ----------------------------------------------------------------------------*/

typedef struct
{
    UART_HandleTypeDef  h_uart;
    QueueHandle_t       q_tx;
} log_bsp_h_t;

/* Private variables -----------------------------------------------------------------------------*/

static log_bsp_h_t gh_log_bsp;

/* Private function prototypes -------------------------------------------------------------------*/

/* Public function bodies ------------------------------------------------------------------------*/

/* Private macros --------------------------------------------------------------------------------*/

#define LOG_BSP_UART                       USART1
#define LOG_BSP_UART_CLK_ENB()             __USART1_CLK_ENABLE();

#define LOG_BSP_UART_TX_GPIO_CLK_ENB()     __GPIOA_CLK_ENABLE();
#define LOG_BSP_UART_TX_PIN                GPIO_PIN_9
#define LOG_BSP_UART_TX_PORT               GPIOA
#define LOG_BSP_UART_TX_MODE               GPIO_MODE_AF_PP

#define LOG_BSP_UART_IRQn                  USART1_IRQn

/**
  * @brief      Initialize logger bsp.
  * @param[in]  p_q_tx: user transmit queue.
  * @param[in]  baud: transfer baud rate.
  * @retval     err_t.
  */
zerr_t
log_bsp_open (const QueueHandle_t* p_q_tx, const uint32_t baud)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	ZTRACE_ASSERT(NULL != p_q_tx);
		
	gh_log_bsp.q_tx = *p_q_tx; /* Update transmit queue */
	LOG_BSP_UART_TX_GPIO_CLK_ENB();  /* Enable TX GPIO clock. */
    LOG_BSP_UART_CLK_ENB();          /* Enable UART clock. */

	/* Configire UART TX pin */
	GPIO_InitStruct.Pin		= LOG_BSP_UART_TX_PIN;
	GPIO_InitStruct.Mode 	= LOG_BSP_UART_TX_MODE;
	GPIO_InitStruct.Pull	= GPIO_PULLDOWN;
	GPIO_InitStruct.Speed	= GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(LOG_BSP_UART_TX_PORT, &GPIO_InitStruct);

	/* Configure the UART parameters. */
	gh_log_bsp.h_uart.Instance = LOG_BSP_UART;
	gh_log_bsp.h_uart.Init.BaudRate = baud;
	gh_log_bsp.h_uart.Init.WordLength = UART_WORDLENGTH_8B;
	gh_log_bsp.h_uart.Init.StopBits = UART_STOPBITS_1;
	gh_log_bsp.h_uart.Init.Parity = UART_PARITY_NONE;
	gh_log_bsp.h_uart.Init.Mode = UART_MODE_TX_RX;
	gh_log_bsp.h_uart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	gh_log_bsp.h_uart.Init.OverSampling = UART_OVERSAMPLING_16;
    HAL_UART_Init(&gh_log_bsp.h_uart);

    /* Configure UART interrupt. */
    HAL_NVIC_SetPriority(LOG_BSP_UART_IRQn, HW_PRIO_LOG_UART, 0);
    HAL_NVIC_EnableIRQ(LOG_BSP_UART_IRQn);
	
	return ZERR_OK;
}

/**
  * @brief  Enable UART TXE interrupt for interrupt process.
  * @param  None.
  * @retval None.
  */
void
log_bsp_enb_tx (void) {
	SET_BIT(gh_log_bsp.h_uart.Instance->CR1, USART_CR1_TXEIE);
}

/**
  * @brief  Handles LOG UART interrupt request.
  * @param  None.
  * @retval None.
  */
void
log_bsp_uart_isr (void) {
    uint32_t sr_val  = READ_REG(gh_log_bsp.h_uart.Instance->SR);
    uint32_t cr1_val = READ_REG(gh_log_bsp.h_uart.Instance->CR1);
    signed char ch = 0;

    /* Don't care if errors occur. */
    /* Don't care receiving mode. */
	
	/* UART in mode Transmitter ------------------------------------------------*/
	if ((RESET != (sr_val & USART_SR_TXE)) && (RESET != (cr1_val & USART_CR1_TXEIE)))
    {
		if (pdTRUE == xQueueReceiveFromISR(gh_log_bsp.q_tx, (void*)&ch, NULL)) {
			gh_log_bsp.h_uart.Instance->DR = ch;
		}
        else
        {   /* Disable the UART Transmit Empty Interrupt. */
            CLEAR_BIT(gh_log_bsp.h_uart.Instance->CR1, USART_CR1_TXEIE);

            /* Enable the UART Transmit Complete Interrupt. */
            SET_BIT(gh_log_bsp.h_uart.Instance->CR1, USART_CR1_TCIE);
        }
        return;
	}
		
		/* UART in mode Transmitter end --------------------------------------------*/
    if ((RESET != (sr_val & USART_SR_TC)) && (RESET != (cr1_val & USART_CR1_TCIE)))
    {
        /* Disable the UART Transmit Complete Interrupt. */
        CLEAR_BIT(gh_log_bsp.h_uart.Instance->CR1, USART_CR1_TCIE);
        return;
    }
}
/* END OF FILE ************************************************************************************/
