/* Includes ------------------------------------------------------------------*/

#include "led.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

static volatile uint8_t LED_counter;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

void MX_LED_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    /* GPIO clock enable */
    LED_GPIO_CLK_ENABLE();

    /* GPIO Configuration */
    GPIO_InitStruct.Pin   = LED_GPIO_PIN;
    GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;

    HAL_GPIO_Init(LED_GPIO_PORT, &GPIO_InitStruct);
}

inline void MX_LED_ON()
{
    LED_counter = 255;

    LED_GPIO_PORT->BSRR = LED_GPIO_PIN;
}

inline void MX_LED_OFF()
{
    if (LED_counter > 0) {
        LED_counter--;
        return;
    }

    LED_GPIO_PORT->BRR = LED_GPIO_PIN;
}