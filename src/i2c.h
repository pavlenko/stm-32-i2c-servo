/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __I2C_H
#define __I2C_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include "main.h"

/* Exported types ------------------------------------------------------------*/

typedef enum {
    I2C_STATUS_READY    = 0,
    I2C_STATUS_LISTEN   = 1,
    I2C_STATUS_BUSY_RX  = 2,
    I2C_STATUS_BUSY_TX  = 3,
    I2C_STATUS_COMPLETE = 4,
} I2C_status_t;

typedef struct {
    I2C_HandleTypeDef *handle;
    I2C_status_t status;
    uint8_t rxBufferData[5];
    uint8_t rxBufferSize;
    uint8_t txBufferData[4];
    uint8_t txBufferSize;
} I2C_t;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported function prototypes --------------------------------------------- */
/* Exported functions ------------------------------------------------------- */

void MX_I2C_Init(I2C_TypeDef *i2c, I2C_HandleTypeDef *handle, uint16_t address);

void MX_I2C_dispatch(I2C_t *i2c);

void MX_I2C_onRequest(I2C_t *i2c);
void MX_I2C_onReceive(I2C_t *i2c);
void MX_I2C_onSuccess(I2C_t *i2c);
void MX_I2C_onFailure(I2C_t *i2c);

#ifdef __cplusplus
}
#endif

#endif //__I2C_H
