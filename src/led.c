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

    HAL_GPIO_WritePin(LED_GPIO_PORT, LED_GPIO_PIN, LED_STATE_ON);
}

inline void MX_LED_OFF()
{
    if (LED_counter > 0) {
        LED_counter--;
        return;
    }

    HAL_GPIO_WritePin(LED_GPIO_PORT, LED_GPIO_PIN, LED_STATE_OFF);
}

inline void MX_LED_PLAY(const uint16_t *data, uint8_t size)
{
    uint8_t index;

    HAL_GPIO_WritePin(LED_GPIO_PORT, LED_GPIO_PIN, LED_STATE_OFF);

    for (index = 0; index < size; index++) {
        HAL_GPIO_TogglePin(LED_GPIO_PORT, LED_GPIO_PIN);
        HAL_Delay((uint32_t) *(data + index));
    }
}