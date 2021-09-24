/* Includes ------------------------------------------------------------------*/

#include "addr.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

void MX_ADDR_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    /* GPIO clock enable */
    __HAL_RCC_GPIOB_CLK_ENABLE();

    /* GPIO Configuration */
    GPIO_InitStruct.Pin   = GPIO_PIN_15|GPIO_PIN_14|GPIO_PIN_13|GPIO_PIN_12;
    GPIO_InitStruct.Mode  = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull  = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

uint8_t MX_ADDR_Read(void)
{
    uint16_t address;

    address = GPIOB->IDR & (GPIO_PIN_15|GPIO_PIN_14|GPIO_PIN_13|GPIO_PIN_12);
    address = address >> 12U;

    return (uint8_t) address;
}
