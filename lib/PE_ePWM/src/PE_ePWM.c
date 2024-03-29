#include "PE_ePWM.h"

/* Includes ------------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

long PE_ePWM_mapRange(long x, long in_min, long in_max, long out_min, long out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

/**
 * Enable/disable PWM generation for channel group
 *
 * If enable timer pre-scale is configured by formula:
 * pre-scale = (F_CPU / (min(PULSE_RES, 65535) * PULSE_CLK)) - 1
 *
 * Where:
 * PULSE_RES - value of PE_ePWM_REG_PULSE_RES register, by default == 65535 TODO default value
 * PULSE_CLK - value of PE_ePWM_REG_PULSE_CLK register, by default == 10000
 *
 * @param pwm
 * @param value
 * @param mask
 */
void PE_ePWM_setEnabledPWM(PE_ePWM_t *pwm, PE_ePWM_BIT_t value, PE_ePWM_EN_PWM_t mask)
{
    if (value == PE_ePWM_BIT_SET) {
        pwm->send(PE_ePWM_CMD_SET_REGISTER_BITS + PE_ePWM_REG_CONFIG, (uint8_t *) &mask, 1);
    } else {
        pwm->send(PE_ePWM_CMD_CLR_REGISTER_BITS + PE_ePWM_REG_CONFIG, (uint8_t *) &mask, 1);
    }
}

/**
 * Enable/disable DC-DC converter for channel group (can be unused)
 *
 * @param pwm
 * @param value
 * @param mask
 */
void PE_ePWM_setEnabledPWR(PE_ePWM_t *pwm, PE_ePWM_BIT_t value, PE_ePWM_EN_PWR_t mask)
{
    if (value == PE_ePWM_BIT_SET) {
        pwm->send(PE_ePWM_CMD_SET_REGISTER_BITS + PE_ePWM_REG_CONFIG, (uint8_t *) &mask, 1);
    } else {
        pwm->send(PE_ePWM_CMD_CLR_REGISTER_BITS + PE_ePWM_REG_CONFIG, (uint8_t *) &mask, 1);
    }
}

/**
 * Enable/disable PWM output for channel(s)
 *
 * @param pwm
 * @param value
 * @param mask
 */
void PE_ePWM_setPulseEN(PE_ePWM_t *pwm, PE_ePWM_BIT_t value, uint8_t mask)
{
    if (value == PE_ePWM_BIT_SET) {
        pwm->send(PE_ePWM_CMD_SET_REGISTER_BITS + PE_ePWM_REG_PULSE_EN, (uint8_t *) &mask, 1);
    } else {
        pwm->send(PE_ePWM_CMD_CLR_REGISTER_BITS + PE_ePWM_REG_PULSE_EN, (uint8_t *) &mask, 1);
    }
}

/**
 * Set PE_ePWM_REG_PULSE_CLK register value
 *
 * @param pwm
 * @param value
 */
void PE_ePWM_setPulseClock(PE_ePWM_t *pwm, uint16_t value)
{
    pwm->send(PE_ePWM_CMD_W_REGISTER + PE_ePWM_REG_PULSE_CLK, (uint8_t *) &value, 2);
}

/**
 * Set PE_ePWM_REG_PULSE_RES register value
 *
 * @param pwm
 * @param value
 */
void PE_ePWM_setPulseReset(PE_ePWM_t *pwm, uint16_t value)
{
    pwm->send(PE_ePWM_CMD_W_REGISTER + PE_ePWM_REG_PULSE_RES, (uint8_t *) &value, 2);
}

/**
 * Set specific channel value as pulse
 *
 * @param pwm
 * @param channel
 * @param value
 */
void PE_ePWM_setPulse(PE_ePWM_t *pwm, PE_ePWM_CHANNEL_N_t channel, uint16_t value)
{
    pwm->send(PE_ePWM_CMD_SET_PULSE + channel, (uint8_t *) &value, 2);
}

/**
 * Set specific channel value as degree
 *
 * @param pwm
 * @param channel
 * @param value
 */
void PE_ePWM_setAngle(PE_ePWM_t *pwm, PE_ePWM_CHANNEL_N_t channel, uint16_t value)
{
    pwm->send(PE_ePWM_CMD_SET_ANGLE + channel, (uint8_t *) &value, 2);
}
