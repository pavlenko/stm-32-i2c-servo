/* Includes ------------------------------------------------------------------*/

#include "tim.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

extern TIM_HandleTypeDef TIM1_Handle;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

void MX_TIM1_Init()
{
    TIM_OC_InitTypeDef sConfigOC;
    TIM_MasterConfigTypeDef sMasterConfig;

    TIM1_Handle.Instance           = TIM1;
    TIM1_Handle.Init.Prescaler     = (uint32_t) (SystemCoreClock / 1000000) - 1;
    TIM1_Handle.Init.CounterMode   = TIM_COUNTERMODE_UP;
    TIM1_Handle.Init.Period        = 20000;
    TIM1_Handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;

    HAL_TIM_PWM_Init(&TIM1_Handle);

    sConfigOC.OCMode     = TIM_OCMODE_PWM1;
    sConfigOC.Pulse      = 1500;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;

    HAL_TIM_PWM_ConfigChannel(&TIM1_Handle, &sConfigOC, TIM_CHANNEL_1);
    HAL_TIM_PWM_ConfigChannel(&TIM1_Handle, &sConfigOC, TIM_CHANNEL_2);
    HAL_TIM_PWM_ConfigChannel(&TIM1_Handle, &sConfigOC, TIM_CHANNEL_3);
    HAL_TIM_PWM_ConfigChannel(&TIM1_Handle, &sConfigOC, TIM_CHANNEL_4);

    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode     = TIM_MASTERSLAVEMODE_ENABLE;

    HAL_TIMEx_MasterConfigSynchronization(&TIM1_Handle, &sMasterConfig);

    HAL_TIM_PWM_Start(&TIM1_Handle, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&TIM1_Handle, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&TIM1_Handle, TIM_CHANNEL_3);
    HAL_TIM_PWM_Start(&TIM1_Handle, TIM_CHANNEL_4);
}

void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef* tim)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    if (tim->Instance == TIM1) {
        /* GPIOA clock enable */
        __HAL_RCC_GPIOA_CLK_ENABLE();

        /* Peripheral clock enable */
        __HAL_RCC_TIM1_CLK_ENABLE();

        /**
         * TIM1 GPIO Configuration
         * PA8  ------> TIM1_CH1
         * PA9  ------> TIM1_CH2
         * PA10 ------> TIM1_CH3
         * PA11 ------> TIM1_CH4
         */
        GPIO_InitStruct.Pin   = GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11;
        GPIO_InitStruct.Mode  = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    }
}

void HAL_TIM_PWM_MspDeInit(TIM_HandleTypeDef* tim)
{
    if (tim->Instance == TIM1) {
        /* Peripheral clock disable */
        __HAL_RCC_TIM1_CLK_DISABLE();

        /**
         * TIM1 GPIO Configuration
         * PA8  ------> TIM1_CH1
         * PA9  ------> TIM1_CH2
         * PA10 ------> TIM1_CH3
         * PA11 ------> TIM1_CH4
         */
        HAL_GPIO_DeInit(GPIOA, GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11);
    }
}
