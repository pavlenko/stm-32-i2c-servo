/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __I2C_H
#define __I2C_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include "main.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported function prototypes --------------------------------------------- */
/* Exported functions ------------------------------------------------------- */

void MX_I2C_Init(I2C_TypeDef *i2c, I2C_HandleTypeDef *handle, uint16_t address);

#ifdef __cplusplus
}
#endif

#endif //__I2C_H
