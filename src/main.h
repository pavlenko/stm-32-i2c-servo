#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined(STM32F1)
#include <stm32f1xx_hal.h>
#elif defined(STM32F0)
#include <stm32f0xx_hal.h>
#else
#error "Unsupported platform"
#endif

void Error_Handler(const char *, int);

#ifdef __cplusplus
}
#endif

#endif //__MAIN_H
