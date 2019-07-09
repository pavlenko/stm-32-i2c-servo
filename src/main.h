/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include <stm32f1xx_hal.h>

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/

#define I2Cx_CLK_ENABLE()               __HAL_RCC_I2C1_CLK_ENABLE()
#define I2Cx_SDA_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOB_CLK_ENABLE()
#define I2Cx_SCL_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOB_CLK_ENABLE()

#define ADDRESS_PORT  GPIOA
#define ADDRESS_PIN_0 GPIO_PIN_0
#define ADDRESS_PIN_1 GPIO_PIN_1
#define ADDRESS_PIN_2 GPIO_PIN_2
#define ADDRESS_PIN_3 GPIO_PIN_3

#define LED_GPIO_CLK_ENABLE() __HAL_RCC_GPIOA_CLK_ENABLE()
#define LED_GPIO_PORT         GPIOA
#define LED_GPIO_PIN          GPIO_PIN_4

#define I2C1_PORT    GPIOA
#define I2C1_PIN_SCL GPIO_PIN_9
#define I2C1_PIN_SDA GPIO_PIN_10

/* Exported functions ------------------------------------------------------- */

void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);
void Error_Handler(const char *, int);

#ifdef __cplusplus
}
#endif

#endif //__MAIN_H
