/* Includes ------------------------------------------------------------------*/

#include "gpio.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

void MX_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    /* GPIOA clock enable */
    __HAL_RCC_GPIOA_CLK_ENABLE();//TODO abstract

    /**
     * Address config GPIO Configuration
     * PB6 ------> I2C1_SCL
     * PB7 ------> I2C1_SDA
     */
    GPIO_InitStruct.Pin   = ADDRESS_PIN_0|ADDRESS_PIN_1|ADDRESS_PIN_2|ADDRESS_PIN_3;
    GPIO_InitStruct.Mode  = GPIO_MODE_INPUT;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

    HAL_GPIO_Init(ADDRESS_PORT, &GPIO_InitStruct);
}
