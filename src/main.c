#include "main.h"

#if defined(STM32F1)
#include <stm32f1xx_hal.h>
#elif defined(STM32F0)
#include <stm32f0xx_hal.h>
#else
#error "Unsupported platform"
#endif

int main(void)
{
    HAL_Init();
}
