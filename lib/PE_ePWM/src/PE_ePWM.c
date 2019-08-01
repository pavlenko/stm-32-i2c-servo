#include "PE_ePWM.h"

/* Includes ------------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

uint8_t PE_ePWM_getRegister(PE_ePWM_t *pwm, uint8_t addr)
{
    uint8_t byte;
    pwm->read(PE_ePWM_CMD_GET_REGISTER + addr, &byte, 1);
    return byte;
}

void PE_ePWM_setRegister(PE_ePWM_t *pwm, uint8_t addr, uint8_t byte)
{
    pwm->send(PE_ePWM_CMD_SET_REGISTER + addr, &byte, 1);
}

void PE_ePWM_clrRegister(PE_ePWM_t *pwm, uint8_t addr, uint8_t byte)
{
    pwm->send(PE_ePWM_CMD_CLR_REGISTER + addr, &byte, 1);
}

void PE_ePWM_setEnabledPWM(PE_ePWM_t *pwm, PE_ePWM_BIT_t value, uint8_t mask)
{
    if (value == PE_ePWM_BIT_SET) {
        pwm->send(PE_ePWM_CMD_SET_REGISTER + PE_ePWM_REG_CONFIG, &mask, 1);
    } else {
        pwm->send(PE_ePWM_CMD_CLR_REGISTER + PE_ePWM_REG_CONFIG, &mask, 1);
    }
}

void PE_ePWM_setEnabledPWR(PE_ePWM_t *pwm, PE_ePWM_BIT_t value, uint8_t mask)
{
    if (value == PE_ePWM_BIT_SET) {
        pwm->send(PE_ePWM_CMD_SET_REGISTER + PE_ePWM_REG_CONFIG, &mask, 1);
    } else {
        pwm->send(PE_ePWM_CMD_CLR_REGISTER + PE_ePWM_REG_CONFIG, &mask, 1);
    }
}

void PE_ePWM_setPulseEN(PE_ePWM_t *pwm, PE_ePWM_BIT_t value, uint8_t mask)
{
    if (value == PE_ePWM_BIT_SET) {
        PE_ePWM_setRegister(pwm, PE_ePWM_REG_PULSE_EN, mask);
    } else {
        PE_ePWM_clrRegister(pwm, PE_ePWM_REG_PULSE_EN, mask);
    }
}

void PE_ePWM_setPulseClock(PE_ePWM_t *pwm, uint16_t value)
{
    pwm->send(PE_ePWM_CMD_SET_REGISTER + PE_ePWM_REG_PULSE_CLK, (uint8_t *) &value, 2);
}

void PE_ePWM_setPulseReset(PE_ePWM_t *pwm, uint16_t value)
{
    pwm->send(PE_ePWM_CMD_SET_REGISTER + PE_ePWM_REG_PULSE_RES, (uint8_t *) &value, 2);
}

void PE_ePWM_setPulse(PE_ePWM_t *pwm, PE_ePWM_CHANNEL_t channel, uint16_t value)
{
    pwm->send(PE_ePWM_CMD_SET_PULSE + channel, (uint8_t *) &value, 2);
}

void PE_ePWM_setAngle(PE_ePWM_t *pwm, PE_ePWM_CHANNEL_t channel, uint16_t value)
{
    pwm->send(PE_ePWM_CMD_SET_ANGLE + channel, (uint8_t *) &value, 2);
}