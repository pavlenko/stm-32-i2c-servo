/* Includes ------------------------------------------------------------------*/

#include <malloc.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <PE_ePWM_device.h>

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

uint8_t PWM_driver_cmd = PWM_DRIVER_CMD_NOP;
uint8_t PWM_driver_reg = PWM_DRIVER_REG_NONE;

typedef struct {
    volatile void *addr;
    uint8_t size;
} PWM_driver_reg_t;

PWM_driver_reg_t PWM_driver_reg_map[8];

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
    MX_TIM_PWM_Init(TIM4, &TIM4_Handle);

    //TODO config other channels
    PWM_driver_reg_map[PWM_DRIVER_REG_CH0_PULSE].addr = &(TIM1_Handle.Instance->CCR1);
    PWM_driver_reg_map[PWM_DRIVER_REG_CH0_PULSE].size = 2;

    PWM_driver_reg_map[PWM_DRIVER_REG_CH1_PULSE].addr = &(TIM1_Handle.Instance->CCR2);
    PWM_driver_reg_map[PWM_DRIVER_REG_CH1_PULSE].size = 2;

    PWM_driver_reg_map[PWM_DRIVER_REG_CH2_PULSE].addr = &(TIM1_Handle.Instance->CCR3);
    PWM_driver_reg_map[PWM_DRIVER_REG_CH2_PULSE].size = 2;

    PWM_driver_reg_map[PWM_DRIVER_REG_CH3_PULSE].addr = &(TIM1_Handle.Instance->CCR4);
    PWM_driver_reg_map[PWM_DRIVER_REG_CH3_PULSE].size = 2;

    PWM_driver_reg_map[PWM_DRIVER_REG_CH4_PULSE].addr = &(TIM4_Handle.Instance->CCR1);
    PWM_driver_reg_map[PWM_DRIVER_REG_CH4_PULSE].size = 2;

    PWM_driver_reg_map[PWM_DRIVER_REG_CH5_PULSE].addr = &(TIM4_Handle.Instance->CCR2);
    PWM_driver_reg_map[PWM_DRIVER_REG_CH5_PULSE].size = 2;

    PWM_driver_reg_map[PWM_DRIVER_REG_CH6_PULSE].addr = &(TIM4_Handle.Instance->CCR3);
    PWM_driver_reg_map[PWM_DRIVER_REG_CH6_PULSE].size = 2;

    PWM_driver_reg_map[PWM_DRIVER_REG_CH7_PULSE].addr = &(TIM4_Handle.Instance->CCR4);
    PWM_driver_reg_map[PWM_DRIVER_REG_CH7_PULSE].size = 2;

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

        MX_I2C_dispatch(&I2Cx);

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

void PE_ePWM_device_updateCH(PE_ePWM_device_t *pwm, PE_ePWM_CHANNEL_N_t channel)
{
    TIM_TypeDef *tim;
    uint8_t num;
    if (channel < 4) {
        num = channel;
        tim = TIM1_Handle.Instance;
    } else {
        num = channel - 4;
        tim = TIM4_Handle.Instance;
    }

    switch (num) {
        case 0:
            tim->CCR1 = pwm->channels[channel].source;
            break;
        case 1:
            tim->CCR2 = pwm->channels[channel].source;
            break;
        case 2:
            tim->CCR3 = pwm->channels[channel].source;
            break;
        case 3:
            tim->CCR4 = pwm->channels[channel].source;
            break;
        default:
            break;
    }
}

/**
 * @param i2c
 */
void MX_I2C_onRequest(I2C_t *i2c)
{
    MX_LED_ON(50);

    if (PWM_driver_cmd == PWM_DRIVER_CMD_R_CODE && PWM_driver_reg != PWM_DRIVER_REG_NONE) {
        //uint16_t value = (uint16_t) TIM1_Handle.Instance->CCR1;
        uint16_t value = (uint16_t) *((__IO uint32_t *) PWM_driver_reg_map[PWM_driver_reg].addr);

        i2c->txBufferData[0] = (uint8_t) value;
        i2c->txBufferData[1] = (uint8_t) (value >> 8U);
        i2c->txBufferSize    = 2;
    }
}

/**
 * @param i2c
 */
void MX_I2C_onReceive(I2C_t *i2c)
{
    (void) i2c;
}

/**
 * @param i2c
 */
void MX_I2C_onSuccess(I2C_t *i2c)
{
    MX_LED_ON(50);

    PWM_driver_cmd = PWM_DRIVER_CMD_NOP;
    PWM_driver_reg = PWM_DRIVER_REG_NONE;

    (void) i2c;
}

/**
 * @param i2c
 */
void MX_I2C_onFailure(I2C_t *i2c)
{
    MX_LED_ON(50);

    PWM_driver_cmd = PWM_DRIVER_CMD_NOP;
    PWM_driver_reg = PWM_DRIVER_REG_NONE;

    (void) i2c;
}

__used void HAL_I2C_AddrCallback(I2C_HandleTypeDef *i2c, uint8_t direction, uint16_t address)
{
    MX_LED_ON(50);

    if (i2c->Instance == I2Cx.handle->Instance) {
        // First of all, check the transfer direction to call the correct Slave Interface
        /*if (direction == I2C_DIRECTION_TRANSMIT) {
            I2Cx.status = I2C_STATUS_BUSY_RX;

            if (HAL_I2C_Slave_Sequential_Receive_IT(i2c, &I2Cx.rxBufferData[I2Cx.rxBufferSize], 1, I2C_FIRST_FRAME) != HAL_OK) {
                Error_Handler(__FILE__, __LINE__);
            }

            I2Cx.rxBufferSize++;
        } else {
            I2Cx.status = I2C_STATUS_BUSY_TX;

            MX_I2C_onRequest(&I2Cx);

            if (HAL_I2C_Slave_Sequential_Transmit_IT(i2c, &I2Cx.txBufferData[0], I2Cx.txBufferSize, I2C_LAST_FRAME) != HAL_OK) {
                Error_Handler(__FILE__, __LINE__);
            }
        }*/
        I2Cx_onAddressReceived(&I2Cx, direction);
    }
}

__used void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *i2c)
{
    MX_LED_ON(50);

    if (i2c->Instance == I2Cx.handle->Instance) {
        /*if (I2Cx.rxBufferSize == 1) {
            if (PWM_DRIVER_CMD_R_CODE == (I2Cx.rxBufferData[0] & ~PWM_DRIVER_CMD_RW_MASK)) {
                PWM_driver_cmd = PWM_DRIVER_CMD_R_CODE;
                PWM_driver_reg = (I2Cx.rxBufferData[0] & PWM_DRIVER_CMD_RW_MASK);
                return;
            }

            if (PWM_DRIVER_CMD_W_CODE == (I2Cx.rxBufferData[0] & ~PWM_DRIVER_CMD_RW_MASK)) {
                PWM_driver_cmd = PWM_DRIVER_CMD_W_CODE;
                PWM_driver_reg = (I2Cx.rxBufferData[0] & PWM_DRIVER_CMD_RW_MASK);
            }
        }

        if (HAL_I2C_Slave_Sequential_Receive_IT(i2c, &I2Cx.rxBufferData[I2Cx.rxBufferSize], 1, I2C_FIRST_FRAME) != HAL_OK) {
            Error_Handler(__FILE__, __LINE__);
        }

        I2Cx.rxBufferSize++;*/
        I2Cx_onSlaveRXCompleted(&I2Cx);
    }
}

__used void HAL_I2C_SlaveTxCpltCallback(I2C_HandleTypeDef *i2c)
{
    MX_LED_ON(50);

    if (i2c->Instance == I2Cx.handle->Instance) {
        I2Cx_onSlaveTXCompleted(&I2Cx);
    }
}

__used void HAL_I2C_ListenCpltCallback(I2C_HandleTypeDef *i2c)
{
    MX_LED_ON(50);

    if (i2c->Instance == I2Cx.handle->Instance) {
        /*if (PWM_driver_cmd == PWM_DRIVER_CMD_W_CODE && PWM_driver_reg != PWM_DRIVER_REG_NONE) {
            uint16_t value = *((uint16_t *) &I2Cx.rxBufferData[1]);
            //TIM1_Handle.Instance->CCR1 = (uint32_t) value;
            *((__IO uint32_t *) PWM_driver_reg_map[PWM_driver_reg].addr) = (uint32_t) value;
        }

        I2Cx.status = I2C_STATUS_SUCCESS;*/
        I2Cx_onListenCompleted(&I2Cx);
    }
}

/*__used void HAL_I2C_AbortCpltCallback(I2C_HandleTypeDef *hi2c)
{
    MX_LED_ON(50);
    UNUSED(hi2c);
}*/

__used void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *i2c)
{
    MX_LED_ON(50);

    if (i2c->Instance == I2Cx.handle->Instance) {
        /*if (HAL_I2C_GetError(i2c) != HAL_I2C_ERROR_AF) {
            Error_Handler(__FILE__, __LINE__);
        }

        I2Cx.status = I2C_STATUS_FAILURE;*/
        I2Cx_onErrorDetected(&I2Cx);
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