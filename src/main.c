/* Includes ------------------------------------------------------------------*/

#include <string.h>

#include "main.h"
#include "i2c.h"
#include "led.h"
#include "tim.h"
#include "addr.h"
#include "pwm_driver.h"

/* Private typedef -----------------------------------------------------------*/

typedef union {
    uint16_t value;
    uint8_t  bytes[2];
} PWM_pulse_t;

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
    uint8_t *rxBufferData;
    uint8_t rxBufferSize;
    uint8_t *txBufferData;
    uint8_t txBufferSize;
} I2C_t;

/* Private define ------------------------------------------------------------*/

#define I2C_RX_BUFFER_MAX 32
#define I2C_TX_BUFFER_MAX 32

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

I2C_HandleTypeDef I2C_Handle;//WARNING do not use directly, at least for now
I2C_t I2Cx = {&I2C_Handle};

TIM_HandleTypeDef TIM1_Handle;
TIM_HandleTypeDef TIM4_Handle;

//TODO collect directly pointers to output compare registers
uint16_t PWM_pulses[] = {0, 0, 0, 0, 0, 0, 0, 0};

uint8_t I2C_rxBufferData[I2C_RX_BUFFER_MAX];
uint8_t I2C_rxBufferSize;
uint8_t I2C_txBufferData[I2C_TX_BUFFER_MAX];
uint8_t I2C_txBufferSize;

uint8_t I2C_responseIndex;
const char* I2C_responseValue[] = {
        "STM32F103xx",
        "1.2.3"
};

uint8_t *I2C_responseData;
uint8_t I2C_responseSize;

/* Private function prototypes -----------------------------------------------*/

void SystemClock_Config(void);

/* Private functions ---------------------------------------------------------*/

/**
 * @brief  Main program
 * @param  None
 * @retval None
 */
int main(void)
{
    uint8_t address;

    HAL_Init();

    SystemClock_Config();

    MX_TIM_PWM_Init(TIM1, &TIM1_Handle);
    MX_TIM_PWM_Init(TIM1, &TIM4_Handle);

    MX_ADDR_Init();
    MX_LED_Init();

    address = MX_ADDR_Read();
    address = address << 1u;

    MX_I2C_Init(I2C2, I2Cx.handle, address);

    uint32_t tick = HAL_GetTick();

    while (1) {
        if (tick < HAL_GetTick()) {
            tick = HAL_GetTick() + 1950;
            MX_LED_ON(50);
        }

        if (I2Cx.status == I2C_STATUS_READY) {
            if (HAL_I2C_EnableListen_IT(I2Cx.handle) != HAL_OK) {
                Error_Handler(__FILE__, __LINE__);
            }

            I2Cx.status = I2C_STATUS_LISTEN;
        }

        if (I2Cx.status == I2C_STATUS_COMPLETE) {
            I2C_rxBufferSize = 0;
            I2C_txBufferSize = 0;

            I2C_responseData = NULL;
            I2C_responseSize = 0;

            I2Cx.txBufferData = NULL;
            I2Cx.txBufferSize = 0;

            I2Cx.rxBufferData = NULL;
            I2Cx.rxBufferSize = 0;

            I2Cx.status = I2C_STATUS_READY;
        }

        MX_LED_OFF(0);
    }
}

/**
 * @brief  System Clock Configuration
 *         The system Clock is configured as follow :
 *            System Clock source            = PLL (HSE)
 *            SYSCLK(Hz)                     = 72000000
 *            HCLK(Hz)                       = 72000000
 *            AHB Prescaler                  = 1
 *            APB1 Prescaler                 = 2
 *            APB2 Prescaler                 = 1
 *            HSE Frequency(Hz)              = 8000000
 *            HSE PREDIV1                    = 1
 *            PLL2MUL                        = 9
 *            Flash Latency(WS)              = 2
 * @param  None
 * @retval None
 */
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    // Initializes the CPU clock source
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState       = RCC_HSE_ON;
    RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
    RCC_OscInitStruct.HSIState       = RCC_HSI_ON;
    RCC_OscInitStruct.PLL.PLLState   = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource  = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLMUL     = RCC_PLL_MUL9;

    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        Error_Handler(__FILE__, __LINE__);
    }

    // Initializes the CPU, AHB and APB buses clocks
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK
                                | RCC_CLOCKTYPE_SYSCLK
                                | RCC_CLOCKTYPE_PCLK1
                                | RCC_CLOCKTYPE_PCLK2;

    RCC_ClkInitStruct.SYSCLKSource   = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider  = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
        Error_Handler(__FILE__, __LINE__);
    }
}

/**
 * @brief  Initializes the Global MSP.
 * @param  None
 * @retval None
 */
void HAL_MspInit(void)
{
    /* Alternate Function I/O clock enable */
    __HAL_RCC_AFIO_CLK_ENABLE();

    /* Power interface clock enable */
    __HAL_RCC_PWR_CLK_ENABLE();
}

/**
 * @brief  DeInitializes the Global MSP.
 * @param  None
 * @retval None
 */
void HAL_MspDeInit(void)
{}

void I2C_receiveCallback()
{}

void I2C_requestCallback()
{}

void HAL_I2C_AddrCallback(I2C_HandleTypeDef *i2c, uint8_t direction, uint16_t address)
{
    MX_LED_ON(50);

    if (i2c->Instance == I2Cx.handle->Instance) {
        // First of all, check the transfer direction to call the correct Slave Interface
        if (direction == I2C_DIRECTION_TRANSMIT) {
            I2Cx.status = I2C_STATUS_BUSY_RX;

            if (HAL_I2C_Slave_Sequential_Receive_IT(i2c, &I2C_rxBufferData[I2C_rxBufferSize], 1, I2C_FIRST_FRAME) != HAL_OK) {
                Error_Handler(__FILE__, __LINE__);
            }

            I2C_rxBufferSize++;
        } else {
            I2Cx.status = I2C_STATUS_BUSY_TX;

            I2C_requestCallback();

//            I2C_responseData = (uint8_t*) (I2C_responseValue[I2C_responseIndex]);
//            I2C_responseSize = strlen((char *) (I2C_responseValue[I2C_responseIndex]));
            if (HAL_I2C_Slave_Sequential_Transmit_IT(i2c, I2C_responseData, I2C_responseSize, I2C_LAST_FRAME) != HAL_OK) {
//            if (HAL_I2C_Slave_Sequential_Transmit_IT(i2c, I2Cx.txBufferData, I2Cx.txBufferSize, I2C_LAST_FRAME) != HAL_OK) {
                Error_Handler(__FILE__, __LINE__);
            }
        }
    }
}

void HAL_I2C_ListenCpltCallback(I2C_HandleTypeDef *i2c)
{
    MX_LED_ON(50);

    if (i2c->Instance == I2Cx.handle->Instance) {
        if (I2Cx.status == I2C_STATUS_BUSY_RX) {
            I2C_receiveCallback();
        }

        I2Cx.status = I2C_STATUS_COMPLETE;
    }
}

void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *i2c)
{
    MX_LED_ON(50);

    if (i2c->Instance == I2Cx.handle->Instance) {
        if (PWM_DRIVER_CMD_R_CODE == (I2C_rxBufferData[0] & ~PWM_DRIVER_CMD_R_MASK)) {
            //TODO test
            I2C_responseData = (uint8_t *) &PWM_pulses[(I2C_rxBufferData[0] & PWM_DRIVER_CMD_R_MASK)];
            I2C_responseSize = 2;
//            I2Cx.txBufferData = (uint8_t *) &PWM_pulses[(I2C_rxBufferData[0] & PWM_DRIVER_CMD_R_MASK)];
//            I2Cx.txBufferSize = 2;
        } else if (PWM_DRIVER_CMD_W_CODE == (I2C_rxBufferData[0] & ~PWM_DRIVER_CMD_W_MASK)) {
            //TODO test

            if (HAL_I2C_Slave_Sequential_Receive_IT(i2c, (uint8_t *) &PWM_pulses[(I2C_rxBufferData[0] & PWM_DRIVER_CMD_R_MASK)], 2, I2C_FIRST_FRAME) != HAL_OK) {
                Error_Handler(__FILE__, __LINE__);
            }

            I2C_rxBufferSize += 2;
        }

//        if (I2C_rxBufferData[0] == 0x00) {
//            I2C_responseIndex = 0;
//        } else if (I2C_rxBufferData[0] == 0x01) {
//            I2C_responseIndex = 1;
//        } else {
//            if (HAL_I2C_Slave_Sequential_Receive_IT(i2c, &I2C_rxBufferData[I2C_rxBufferSize], 1, I2C_FIRST_FRAME) != HAL_OK) {
//                Error_Handler(__FILE__, __LINE__);
//            }
//
//            I2C_rxBufferSize++;
//        }
    }
}

void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *i2c)
{
    MX_LED_ON(50);

    if (i2c->Instance == I2Cx.handle->Instance) {
        if (HAL_I2C_GetError(i2c) != HAL_I2C_ERROR_AF) {
            Error_Handler(__FILE__, __LINE__);
        }

        I2Cx.status = I2C_STATUS_COMPLETE;
    }
}

/**
 * @brief  This function handles I2C2 event interrupt.
 * @param  None
 * @retval None
 */
void I2C1_EV_IRQHandler(void)
{
    if (I2C1 == I2Cx.handle->Instance) {
        HAL_I2C_EV_IRQHandler(I2Cx.handle);
    }
}

/**
 * @brief This function handles I2C2 error interrupt.
 * @param  None
 * @retval None
 */
void I2C1_ER_IRQHandler(void)
{
    if (I2C1 == I2Cx.handle->Instance) {
        HAL_I2C_ER_IRQHandler(I2Cx.handle);
    }
}

/**
 * @brief  This function handles I2C2 event interrupt.
 * @param  None
 * @retval None
 */
void I2C2_EV_IRQHandler(void)
{
    if (I2C2 == I2Cx.handle->Instance) {
        HAL_I2C_EV_IRQHandler(I2Cx.handle);
    }
}

/**
 * @brief This function handles I2C2 error interrupt.
 * @param  None
 * @retval None
 */
void I2C2_ER_IRQHandler(void)
{
    if (I2C2 == I2Cx.handle->Instance) {
        HAL_I2C_ER_IRQHandler(I2Cx.handle);
    }
}

/**
 * @brief   This function handles NMI exception.
 * @param  None
 * @retval None
 */
void NMI_Handler(void)
{}

/**
 * @brief  This function handles Hard Fault exception.
 * @param  None
 * @retval None
 */
void HardFault_Handler(void)
{
    /* Go to infinite loop when Hard Fault exception occurs */
    while (1) {
        __NOP();
    }
}

/**
 * @brief  This function handles Memory Manage exception.
 * @param  None
 * @retval None
 */
void MemManage_Handler(void)
{
    /* Go to infinite loop when Memory Manage exception occurs */
    while (1) {
        __NOP();
    }
}

/**
 * @brief  This function handles Bus Fault exception.
 * @param  None
 * @retval None
 */
void BusFault_Handler(void)
{
    /* Go to infinite loop when Bus Fault exception occurs */
    while (1) {
        __NOP();
    }
}

/**
 * @brief  This function handles Usage Fault exception.
 * @param  None
 * @retval None
 */
void UsageFault_Handler(void)
{
    /* Go to infinite loop when Usage Fault exception occurs */
    while (1) {
        __NOP();
    }
}

/**
 * @brief  This function handles SVCall exception.
 * @param  None
 * @retval None
 */
void SVC_Handler(void)
{}

/**
 * @brief  This function handles Debug Monitor exception.
 * @param  None
 * @retval None
 */
void DebugMon_Handler(void)
{}

/**
 * @brief  This function handles PendSVC exception.
 * @param  None
 * @retval None
 */
void PendSV_Handler(void)
{}

/**
 * @brief  This function handles SysTick Handler.
 * @param  None
 * @retval None
 */
void SysTick_Handler(void)
{
    HAL_IncTick();
}

/**
 * @brief This function is executed in case of error occurrence.
 *
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void Error_Handler(const char * file, int line)
{
    UNUSED(file);
    UNUSED(line);

    const uint16_t sequence[] = {
            100,
            200,
            100,
            200,
            100,
            1200,
    };

    while (1) {
        MX_LED_PLAY(sequence, 6);
        __NOP();
    }
}

#ifdef USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t* file, uint32_t line)
{
    UNUSED(file);
    UNUSED(line);
}
#endif