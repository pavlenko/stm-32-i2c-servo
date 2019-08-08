/* Includes ------------------------------------------------------------------*/

#include "i2c.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

void MX_I2C_Init(I2C_TypeDef *i2c, I2C_HandleTypeDef *handle, uint16_t address)
{
    handle->Instance             = i2c;
    handle->Init.ClockSpeed      = 400000;
    handle->Init.DutyCycle       = I2C_DUTYCYCLE_2;
    handle->Init.OwnAddress1     = address;
    handle->Init.OwnAddress2     = 0xFF;
    handle->Init.AddressingMode  = I2C_ADDRESSINGMODE_7BIT;
    handle->Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    handle->Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    handle->Init.NoStretchMode   = I2C_NOSTRETCH_DISABLE;

    if (HAL_I2C_Init(handle) != HAL_OK) {
        Error_Handler(__FILE__, __LINE__);
    }
}

void MX_I2C_dispatch(I2C_t *i2c)
{
    if (i2c->status == I2C_STATUS_READY) {
        if (HAL_I2C_EnableListen_IT(i2c->handle) != HAL_OK) {
            Error_Handler(__FILE__, __LINE__);
        }

        i2c->status = I2C_STATUS_LISTEN;
    }

    if (i2c->status == I2C_STATUS_SUCCESS) {
        MX_I2C_onSuccess(i2c);
    }

    if (i2c->status == I2C_STATUS_FAILURE) {
        MX_I2C_onFailure(i2c);
    }

    if (i2c->status == I2C_STATUS_SUCCESS || i2c->status == I2C_STATUS_FAILURE) {
        i2c->txBufferSize = 0;
        i2c->rxBufferSize = 0;

        i2c->status = I2C_STATUS_READY;
    }
}

/**
 * Called in I2C slave TX mode after address received
 *
 * @param i2c
 */
__attribute__((weak)) void MX_I2C_onRequest(I2C_t *i2c)
{
    (void) i2c;
}

/**
 * Called in I2C slave RX mode after address and data received
 *
 * @param i2c
 */
__attribute__((weak)) void MX_I2C_onReceive(I2C_t *i2c)
{
    (void) i2c;
}

/**
 * Called after RX/TX transaction completed successfully
 *
 * @param i2c
 */
__attribute__((weak)) void MX_I2C_onSuccess(I2C_t *i2c)
{
    (void) i2c;
}

/**
 * Called in I2C error callback
 *
 * @param i2c
 */
__attribute__((weak)) void MX_I2C_onFailure(I2C_t *i2c)
{
    (void) i2c;
}

void I2Cx_onAddressReceived(I2C_t *i2c, uint8_t direction)
{
    // First of all, check the transfer direction to call the correct Slave Interface
    if (direction == I2C_DIRECTION_TRANSMIT) {
        i2c->status = I2C_STATUS_BUSY_RX;

        if (HAL_I2C_Slave_Sequential_Receive_IT(i2c->handle, &(i2c->rxBufferData[i2c->rxBufferSize]), 1, I2C_FIRST_FRAME) != HAL_OK) {
            Error_Handler(__FILE__, __LINE__);
        }

        i2c->rxBufferSize++;
    } else {
        i2c->status = I2C_STATUS_BUSY_TX;

        MX_I2C_onRequest(i2c);

        if (HAL_I2C_Slave_Sequential_Transmit_IT(i2c->handle, &(i2c->txBufferData[0]), i2c->txBufferSize, I2C_LAST_FRAME) != HAL_OK) {
            Error_Handler(__FILE__, __LINE__);
        }
    }
}

void I2Cx_onSlaveRXCompleted(I2C_t *i2c)
{
    if (HAL_I2C_Slave_Sequential_Receive_IT(i2c->handle, &(i2c->rxBufferData[i2c->rxBufferSize]), 1, I2C_FIRST_FRAME) != HAL_OK) {
        Error_Handler(__FILE__, __LINE__);
    }

    i2c->rxBufferSize++;
}

void I2Cx_onSlaveTXCompleted(I2C_t *i2c)
{
    i2c->txBufferSize = 0;
}

void I2Cx_onListenCompleted(I2C_t *i2c)
{
    MX_I2C_onReceive(i2c);
    i2c->status = I2C_STATUS_SUCCESS;
}

void I2Cx_onErrorDetected(I2C_t *i2c)
{
    if (HAL_I2C_GetError(i2c->handle) != HAL_I2C_ERROR_AF) {
        Error_Handler(__FILE__, __LINE__);
    }

    i2c->status = I2C_STATUS_FAILURE;
}

void HAL_I2C_MspInit(I2C_HandleTypeDef* i2c)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    if (i2c->Instance == I2C1) {
        /* I2C clock enable */
        __HAL_RCC_I2C1_CLK_ENABLE();

        /* GPIO clock enable */
        __HAL_RCC_GPIOB_CLK_ENABLE();

        /**
         * I2C GPIO Configuration
         * PB6 ------> I2C_SCL
         * PB7 ------> I2C_SDA
         */
        GPIO_InitStruct.Pin   = GPIO_PIN_6|GPIO_PIN_7;
        GPIO_InitStruct.Mode  = GPIO_MODE_AF_OD;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

        /* I2C interrupt Init */
        HAL_NVIC_SetPriority(I2C1_EV_IRQn, 1, 1);
        HAL_NVIC_EnableIRQ(I2C1_EV_IRQn);

        HAL_NVIC_SetPriority(I2C1_ER_IRQn, 1, 0);
        HAL_NVIC_EnableIRQ(I2C1_ER_IRQn);
    }

    if (i2c->Instance == I2C2) {
        /* I2C clock enable */
        __HAL_RCC_I2C2_CLK_ENABLE();

        /* GPIO clock enable */
        __HAL_RCC_GPIOB_CLK_ENABLE();

        /**
         * I2C GPIO Configuration
         * PB10 ------> I2C_SCL
         * PB11 ------> I2C_SDA
         */
        GPIO_InitStruct.Pin   = GPIO_PIN_10|GPIO_PIN_11;
        GPIO_InitStruct.Mode  = GPIO_MODE_AF_OD;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

        /* I2C interrupt Init */
        HAL_NVIC_SetPriority(I2C2_EV_IRQn, 1, 1);
        HAL_NVIC_EnableIRQ(I2C2_EV_IRQn);

        HAL_NVIC_SetPriority(I2C2_ER_IRQn, 1, 0);
        HAL_NVIC_EnableIRQ(I2C2_ER_IRQn);
    }
}

void HAL_I2C_MspDeInit(I2C_HandleTypeDef* i2c)
{
    if (i2c->Instance == I2C1) {
        /* I2C clock disable */
        __HAL_RCC_I2C1_CLK_DISABLE();

        /**
         * I2C GPIO Configuration
         * PB6 ------> I2C_SCL
         * PB7 ------> I2C_SDA
         */
        HAL_GPIO_DeInit(GPIOB, GPIO_PIN_6|GPIO_PIN_7);

        /* I2C interrupt Deinit */
        HAL_NVIC_DisableIRQ(I2C1_EV_IRQn);
        HAL_NVIC_DisableIRQ(I2C1_ER_IRQn);
    }

    if (i2c->Instance == I2C2) {
        /* I2C clock disable */
        __HAL_RCC_I2C2_CLK_DISABLE();

        /**
         * I2C GPIO Configuration
         * PB6 ------> I2C_SCL
         * PB7 ------> I2C_SDA
         */
        HAL_GPIO_DeInit(GPIOB, GPIO_PIN_10|GPIO_PIN_11);

        /* I2C interrupt Deinit */
        HAL_NVIC_DisableIRQ(I2C2_EV_IRQn);
        HAL_NVIC_DisableIRQ(I2C2_ER_IRQn);
    }
}