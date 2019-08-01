#include "PE_ePWM.h"

/* Includes ------------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

void PE_ePWM_setEnabledPWM(PE_ePWM_t *pwm, PE_ePWM_BIT_t value, PE_ePWM_EN_PWM_t mask)
{
    if (value == PE_ePWM_BIT_SET) {
        pwm->send(PE_ePWM_CMD_SET_REGISTER_BITS + PE_ePWM_REG_CONFIG, (uint8_t *) &mask, 1);
    } else {
        pwm->send(PE_ePWM_CMD_CLR_REGISTER_BITS + PE_ePWM_REG_CONFIG, (uint8_t *) &mask, 1);
    }
}

void PE_ePWM_setEnabledPWR(PE_ePWM_t *pwm, PE_ePWM_BIT_t value, PE_ePWM_EN_PWR_t mask)
{
    if (value == PE_ePWM_BIT_SET) {
        pwm->send(PE_ePWM_CMD_SET_REGISTER_BITS + PE_ePWM_REG_CONFIG, (uint8_t *) &mask, 1);
    } else {
        pwm->send(PE_ePWM_CMD_CLR_REGISTER_BITS + PE_ePWM_REG_CONFIG, (uint8_t *) &mask, 1);
    }
}

void PE_ePWM_setPulseEN(PE_ePWM_t *pwm, PE_ePWM_BIT_t value, uint8_t mask)
{
    if (value == PE_ePWM_BIT_SET) {
        pwm->send(PE_ePWM_CMD_SET_REGISTER_BITS + PE_ePWM_REG_PULSE_EN, (uint8_t *) &mask, 1);
    } else {
        pwm->send(PE_ePWM_CMD_CLR_REGISTER_BITS + PE_ePWM_REG_PULSE_EN, (uint8_t *) &mask, 1);
    }
}

void PE_ePWM_setPulseClock(PE_ePWM_t *pwm, uint16_t value)
{
    pwm->send(PE_ePWM_CMD_W_REGISTER + PE_ePWM_REG_PULSE_CLK, (uint8_t *) &value, 2);
}

void PE_ePWM_setPulseReset(PE_ePWM_t *pwm, uint16_t value)
{
    pwm->send(PE_ePWM_CMD_W_REGISTER + PE_ePWM_REG_PULSE_RES, (uint8_t *) &value, 2);
}

void PE_ePWM_setPulse(PE_ePWM_t *pwm, PE_ePWM_CHANNEL_t channel, uint16_t value)
{
    pwm->send(PE_ePWM_CMD_SET_PULSE + channel, (uint8_t *) &value, 2);
}

void PE_ePWM_setAngle(PE_ePWM_t *pwm, PE_ePWM_CHANNEL_t channel, uint16_t value)
{
    pwm->send(PE_ePWM_CMD_SET_ANGLE + channel, (uint8_t *) &value, 2);
}