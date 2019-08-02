/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include <stm32f1xx_hal.h>

/* Exported types ------------------------------------------------------------*/

//TODO maybe move this type to I2C file
enum {
    I2C_STATUS_READY    = 0,
    I2C_STATUS_LISTEN   = 1,
    I2C_STATUS_BUSY_RX  = 2,
    I2C_STATUS_BUSY_TX  = 3,
    I2C_STATUS_COMPLETE = 4,
} I2C_status_t;

typedef struct {
    I2C_HandleTypeDef *handle;
    uint8_t status;
    uint8_t rxBufferData[5];
    uint8_t rxBufferSize;
    uint8_t txBufferData[4];
    uint8_t txBufferSize;
} I2C_t;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

void I2C1_EV_IRQHandler(void);
void I2C1_ER_IRQHandler(void);
void I2C2_EV_IRQHandler(void);
void I2C2_ER_IRQHandler(void);
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
