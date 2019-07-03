#ifndef __I2C_H
#define __I2C_H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

#define I2C_OWN_ADDRESS_1 0x3C
#define I2C_OWN_ADDRESS_2 0xFF

extern I2C_HandleTypeDef i2c1;

void MX_I2C1_Init();

#ifdef __cplusplus
}
#endif

#endif //__I2C_H
