/* Includes ------------------------------------------------------------------*/

#include "PE_ePWM_device.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

long PE_ePWM_device_map(long x, long in_min, long in_max, long out_min, long out_max);

/* Private functions ---------------------------------------------------------*/

void PE_ePWM_device_onReceive(PE_ePWM_device_t *pwm, uint8_t *data, uint8_t size)
{
    // Resolve command
    if (pwm->cmd == PE_ePWM_CMD_NOP) {
        pwm->cmd = *data & ~PE_ePWM_REG_MASK;
        pwm->reg = *data & PE_ePWM_REG_MASK;
    }

    // Decode command
    switch (pwm->cmd) {
        case PE_ePWM_CMD_W_REGISTER:
            pwm->registers[pwm->reg] = *(data + 1);
            break;
        case PE_ePWM_CMD_SET_REGISTER_BITS:
            pwm->registers[pwm->reg] |= *(data + 1);
            break;
        case PE_ePWM_CMD_CLR_REGISTER_BITS:
            pwm->registers[pwm->reg] &= (uint8_t) ~(*(data + 1));
            break;
        case PE_ePWM_CMD_SET_PULSE:
            if (size >= 5) {
                pwm->periods[pwm->reg] = (uint16_t) *(data + 3);
            } else {
                pwm->periods[pwm->reg] = 0;
            }

            pwm->pulses[pwm->reg] = (uint16_t) *(data + 1);
            break;
        case PE_ePWM_CMD_SET_ANGLE:
            if ((pwm->registers[PE_ePWM_REG_CONFIG] & PE_ePWM_CONFIG_MODE) != PE_ePWM_MODE_SERVO) {
                if (size >= 5) {
                    pwm->periods[pwm->reg] = (uint16_t) *(data + 3);
                } else {
                    pwm->periods[pwm->reg] = 0;
                }

                pwm->pulses[pwm->reg] = (uint16_t) PE_ePWM_device_map(
                        *(data + 1),
                        0,
                        18000,
                        pwm->min[pwm->reg],
                        pwm->max[pwm->reg]
                );
            }
            break;
    }

    //TODO update calibration if we enter servo mode
}

/**
 * Executed after data direction changed from TX to RX
 *
 * @param pwm
 * @param data
 * @param size
 */
void PE_ePWM_device_onRequest(PE_ePWM_device_t *pwm, uint8_t *data, uint8_t *size)
{
    // Decode command & set response
    switch (pwm->cmd) {
        case PE_ePWM_CMD_R_REGISTER:
            memcpy(data, &(pwm->registers[pwm->reg]), 1);
            *size = 1;
            break;
        case PE_ePWM_CMD_GET_PULSE:
            memcpy(data, &(pwm->channels[pwm->reg].source), 2);
            *size = 2;
            break;
        case PE_ePWM_CMD_GET_ANGLE:
            if ((pwm->registers[PE_ePWM_REG_CONFIG] & PE_ePWM_CONFIG_MODE) == PE_ePWM_MODE_SERVO) {
                uint16_t angle = PE_ePWM_device_map(
                        pwm->channels[pwm->reg].source,
                        pwm->channels[pwm->reg].min,
                        pwm->channels[pwm->reg].max,
                        0,
                        18000
                );

                memcpy(data, &angle, 2);
                *size = 2;
            }
            break;
    }

    // Reset command code & register code
    pwm->cmd = PE_ePWM_CMD_NOP;
    pwm->reg = PE_ePWM_REG_NONE;
}

void PE_ePWM_device_dispatch(PE_ePWM_device_t *pwm)
{
    for (uint8_t i = 0; i < 8; i++) {
        if (pwm->channels[i].target == pwm->channels[i].source) {
            pwm->channels[i].step = 0;
            continue;
        }

        if (pwm->channels[i].step) {
            if (pwm->channels[i].target > pwm->channels[i].source) {
                pwm->channels[i].source += pwm->channels[i].step;

                if (pwm->channels[i].target <= pwm->channels[i].source) {
                    pwm->channels[i].source = pwm->channels[i].target;
                    pwm->channels[i].step   = 0;
                }
            } else {
                pwm->channels[i].source -= pwm->channels[i].step;

                if (pwm->channels[i].target >= pwm->channels[i].source) {
                    pwm->channels[i].source = pwm->channels[i].target;
                    pwm->channels[i].step   = 0;
                }
            }
        }

        PE_ePWM_device_updateCH(pwm, i);
    }
}

__attribute__((weak)) void PE_ePWM_device_updateCH(PE_ePWM_device_t *pwm, PE_ePWM_CHANNEL_N_t channel)
{
    (void) pwm;
    (void) channel;
}

long PE_ePWM_device_map(long x, long in_min, long in_max, long out_min, long out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

/**
 * @param source   current servo pulse width
 * @param target   target servo pulse width
 * @param duration time to reach target pulse width in seconds (maybe better use millis?)
 * @return
 */
uint16_t ____calculateStep(uint16_t source, uint16_t target, uint16_t duration)
{
    int diff = abs(source - target);

    return diff / duration;
}

void ____setPulse(PE_ePWM_device_t *pwm, PE_ePWM_CHANNEL_N_t channel, uint16_t pulse, uint16_t durationMS)
{
    pwm->channels[channel].step = abs(pulse - pwm->channels[channel].source) / (durationMS / 20000);

    if (pwm->channels[channel].step > 0) {
        pwm->channels[channel].target = pulse;
    } else {
        pwm->channels[channel].source = pulse;
        pwm->channels[channel].target = pulse;

        PE_ePWM_device_updateCH(pwm, channel);
    }
}

void ____setEnabledPWMGlobal(uint8_t val, uint8_t mask)
{
    uint16_t pulse_res = 20000;//TODO if servo mode use 20000 value else from reg
    uint16_t pulse_clk = 50;//TODO if servo mode use 50 value else from reg
    uint32_t pre_scale = (SystemCoreClock / (pulse_res * pulse_clk)) - 1;

    if (mask & 0x01U) {
        if (val) {
            TIM1_Handle.Instance->ARR = (uint32_t) pulse_res;
            TIM1_Handle.Instance->PSC = (uint32_t) pre_scale;

            TIM1_Handle.Instance->BDTR |= (TIM_BDTR_MOE);
        } else {
            TIM1_Handle.Instance->BDTR &= ~(TIM_BDTR_MOE);
        }
    }

    if (mask & 0x02U) {
        if (val) {
            TIM4_Handle.Instance->ARR = (uint32_t) pulse_res;
            TIM4_Handle.Instance->PSC = (uint32_t) pre_scale;

            TIM4_Handle.Instance->BDTR |= (TIM_BDTR_MOE);
        } else {
            TIM4_Handle.Instance->BDTR &= ~(TIM_BDTR_MOE);
        }
    }
}

//TODO weak
void ____setEnabledPWMChannel(uint8_t val, uint8_t mask)
{
    uint8_t mask1 = mask & 0x0FU; // Get lower 4 bits as mask for group 1
    uint8_t mask2 = mask >> 4U;   // Get upper 4 bits as mask for group 2

    HAL_StatusTypeDef (*callable)(TIM_HandleTypeDef *handle, uint32_t channel);

    if (val) {
        callable = HAL_TIM_PWM_Start; // If enable requested - start channel PWM
    } else {
        callable = HAL_TIM_PWM_Stop; // If disable requested - stop channel PWM
    }

    // Process group 1
    if (mask1 & TIM_CHANNEL_1) {
        callable(&TIM1_Handle, TIM_CHANNEL_1);
    }
    if (mask1 & TIM_CHANNEL_2) {
        callable(&TIM1_Handle, TIM_CHANNEL_2);
    }
    if (mask1 & TIM_CHANNEL_3) {
        callable(&TIM1_Handle, TIM_CHANNEL_3);
    }
    if (mask1 & TIM_CHANNEL_4) {
        callable(&TIM1_Handle, TIM_CHANNEL_4);
    }

    // Process group 2
    if (mask2 & TIM_CHANNEL_1) {
        callable(&TIM4_Handle, TIM_CHANNEL_1);
    }
    if (mask2 & TIM_CHANNEL_2) {
        callable(&TIM4_Handle, TIM_CHANNEL_2);
    }
    if (mask2 & TIM_CHANNEL_3) {
        callable(&TIM4_Handle, TIM_CHANNEL_3);
    }
    if (mask2 & TIM_CHANNEL_4) {
        callable(&TIM4_Handle, TIM_CHANNEL_4);
    }
}