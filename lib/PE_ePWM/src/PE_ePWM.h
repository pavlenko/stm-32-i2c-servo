/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef PE_ePWM_H
#define PE_ePWM_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include <stdint.h>

/* Exported constants --------------------------------------------------------*/

/** Instructions **************************************************************/

#define PE_ePWM_CMD_R_REGISTER        0x00U // Get register
#define PE_ePWM_CMD_W_REGISTER        0x08U // Set register (overwrite value)
#define PE_ePWM_CMD_SET_REGISTER_BITS 0x10U // Set register bits to 1
#define PE_ePWM_CMD_CLR_REGISTER_BITS 0x18U // Set register bits to 0
#define PE_ePWM_CMD_GET_PULSE         0x20U // Get channel pulse width
#define PE_ePWM_CMD_SET_PULSE         0x28U // Set channel pulse width
#define PE_ePWM_CMD_GET_ANGLE         0x30U // Get channel degree, only for servo mode
#define PE_ePWM_CMD_SET_ANGLE         0x38U // Set channel degree, only for servo mode

#define PE_ePWM_CMD_GET_CALIBRATION_MIN 0x40U
#define PE_ePWM_CMD_SET_CALIBRATION_MIN 0x48U
#define PE_ePWM_CMD_GET_CALIBRATION_MAX 0x50U
#define PE_ePWM_CMD_SET_CALIBRATION_MAX 0x58U

#define PE_ePWM_CMD_NOP               0xFFU

/** Registers *****************************************************************/

#define PE_ePWM_REG_CONFIG    0x00U // 8 bit
#define PE_ePWM_REG_PULSE_EN  0x01U // 8 bit
#define PE_ePWM_REG_PULSE_CLK 0x02U // 16 bit Configure pulse clock HZ
#define PE_ePWM_REG_PULSE_RES 0x03U // 16 bit Configure pulse reset value

#define PE_ePWM_REG_RESERVED0 0x04U
#define PE_ePWM_REG_RESERVED1 0x05U
#define PE_ePWM_REG_RESERVED2 0x06U
#define PE_ePWM_REG_RESERVED3 0x07U

#define PE_ePWM_REG_MASK      0x07U
#define PE_ePWM_REG_NONE      0xFFU

/** Values ********************************************************************/

#define PE_ePWM_REG_PULSE_CH0 0x08U
#define PE_ePWM_REG_PULSE_CH1 0x09U
#define PE_ePWM_REG_PULSE_CH2 0x0AU
#define PE_ePWM_REG_PULSE_CH3 0x0BU
#define PE_ePWM_REG_PULSE_CH4 0x0CU
#define PE_ePWM_REG_PULSE_CH5 0x0DU
#define PE_ePWM_REG_PULSE_CH6 0x0EU
#define PE_ePWM_REG_PULSE_CH7 0x0FU

#define PE_ePWM_REG_MIN_CH0   0x10U
#define PE_ePWM_REG_MIN_CH1   0x11U
#define PE_ePWM_REG_MIN_CH2   0x12U
#define PE_ePWM_REG_MIN_CH3   0x13U
#define PE_ePWM_REG_MIN_CH4   0x14U
#define PE_ePWM_REG_MIN_CH5   0x15U
#define PE_ePWM_REG_MIN_CH6   0x16U
#define PE_ePWM_REG_MIN_CH7   0x17U

#define PE_ePWM_REG_MAX_CH0   0x18U
#define PE_ePWM_REG_MAX_CH1   0x19U
#define PE_ePWM_REG_MAX_CH2   0x1AU
#define PE_ePWM_REG_MAX_CH3   0x1BU
#define PE_ePWM_REG_MAX_CH4   0x1CU
#define PE_ePWM_REG_MAX_CH5   0x1DU
#define PE_ePWM_REG_MAX_CH6   0x1EU
#define PE_ePWM_REG_MAX_CH7   0x1FU

/* Exported macro ------------------------------------------------------------*/

/** CONFIG bits ***************************************************************/

#define PE_ePWM_CONFIG_MODE_Pos    (0x00U)
#define PE_ePWM_CONFIG_MODE_Msk    (0x03U << PE_ePWM_CONFIG_MODE_Pos)
#define PE_ePWM_CONFIG_MODE        PE_ePWM_CONFIG_MODE_Msk

#define PE_ePWM_CONFIG_MODE0_Pos   (0x00U)
#define PE_ePWM_CONFIG_MODE0_Msk   (0x01U << PE_ePWM_CONFIG_MODE0_Pos)
#define PE_ePWM_CONFIG_MODE0       PE_ePWM_CONFIG_MODE0_Msk

#define PE_ePWM_CONFIG_MODE1_Pos   (0x01U)
#define PE_ePWM_CONFIG_MODE1_Msk   (0x01U << PE_ePWM_CONFIG_MODE1_Pos)
#define PE_ePWM_CONFIG_MODE1       PE_ePWM_CONFIG_MODE1_Msk

// Enable power output for CH0-CH3
#define PE_ePWM_CONFIG_EN_PWR0_Pos (0x02U)
#define PE_ePWM_CONFIG_EN_PWR0_Msk (0x01U << PE_ePWM_CONFIG_EN_PWR0_Pos)
#define PE_ePWM_CONFIG_EN_PWR0     PE_ePWM_CONFIG_EN_PWR0_Msk

// Enable power output for CH4-CH7
#define PE_ePWM_CONFIG_EN_PWR1_Pos (0x03U)
#define PE_ePWM_CONFIG_EN_PWR1_Msk (0x01U << PE_ePWM_CONFIG_EN_PWR1_Pos)
#define PE_ePWM_CONFIG_EN_PWR1     PE_ePWM_CONFIG_EN_PWR1_Msk

// Enable PWM generation for CH0-CH3
#define PE_ePWM_CONFIG_EN_PWM0_Pos (0x04U)
#define PE_ePWM_CONFIG_EN_PWM0_Msk (0x01U << PE_ePWM_CONFIG_EN_PWM0_Pos)
#define PE_ePWM_CONFIG_EN_PWM0     PE_ePWM_CONFIG_EN_PWM0_Msk

// Enable PWM generation for CH4-CH7
#define PE_ePWM_CONFIG_EN_PWM1_Pos (0x05U)
#define PE_ePWM_CONFIG_EN_PWM1_Msk (0x01U << PE_ePWM_CONFIG_EN_PWM1_Pos)
#define PE_ePWM_CONFIG_EN_PWM1     PE_ePWM_CONFIG_EN_PWM1_Msk

/** CH bits *******************************************************************/

#define PE_ePWM_CH0_Pos (0x00U)
#define PE_ePWM_CH0_Msk (0x01U << PE_ePWM_CH0_Pos)
#define PE_ePWM_CH0     PE_ePWM_CH0_Msk

#define PE_ePWM_CH1_Pos (0x01U)
#define PE_ePWM_CH1_Msk (0x01U << PE_ePWM_CH1_Pos)
#define PE_ePWM_CH1     PE_ePWM_CH1_Msk

#define PE_ePWM_CH2_Pos (0x02U)
#define PE_ePWM_CH2_Msk (0x01U << PE_ePWM_CH2_Pos)
#define PE_ePWM_CH2     PE_ePWM_CH2_Msk

#define PE_ePWM_CH3_Pos (0x03U)
#define PE_ePWM_CH3_Msk (0x01U << PE_ePWM_CH3_Pos)
#define PE_ePWM_CH3     PE_ePWM_CH3_Msk

#define PE_ePWM_CH4_Pos (0x04U)
#define PE_ePWM_CH4_Msk (0x01U << PE_ePWM_CH4_Pos)
#define PE_ePWM_CH4     PE_ePWM_CH4_Msk

#define PE_ePWM_CH5_Pos (0x05U)
#define PE_ePWM_CH5_Msk (0x01U << PE_ePWM_CH5_Pos)
#define PE_ePWM_CH5     PE_ePWM_CH5_Msk

#define PE_ePWM_CH6_Pos (0x06U)
#define PE_ePWM_CH6_Msk (0x01U << PE_ePWM_CH6_Pos)
#define PE_ePWM_CH6     PE_ePWM_CH6_Msk

#define PE_ePWM_CH7_Pos (0x07U)
#define PE_ePWM_CH7_Msk (0x01U << PE_ePWM_CH7_Pos)
#define PE_ePWM_CH7     PE_ePWM_CH7_Msk

#define PE_ePWM_CH_ALL  0xFFU

/* Exported types ------------------------------------------------------------*/

typedef enum {
    PE_ePWM_RESULT_OK    = 0x00U,
    PE_ePWM_RESULT_ERROR = 0x01U,
} PE_ePWM_RESULT_t;

typedef enum {
    PE_ePWM_BIT_CLR = 0x00U,
    PE_ePWM_BIT_SET = 0x01U,
} PE_ePWM_BIT_t;

typedef enum {
    PE_ePWM_MODE_PULSE     = 0x00U,
    PE_ePWM_MODE_SERVO     = PE_ePWM_CONFIG_MODE0,
    PE_ePWM_MODE_RESERVED0 = PE_ePWM_CONFIG_MODE1,
    PE_ePWM_MODE_RESERVED1 = PE_ePWM_CONFIG_MODE1|PE_ePWM_CONFIG_MODE0,
} PE_ePWM_MODE_t;

typedef enum {
    PE_ePWM_EN_PWR_NONE    = 0x00U,
    PE_ePWM_EN_PWR_GROUP0  = PE_ePWM_CONFIG_EN_PWR0,
    PE_ePWM_EN_PWR_GROUP1  = PE_ePWM_CONFIG_EN_PWR1,
    PE_ePWM_EN_PWR_ALL     = PE_ePWM_CONFIG_EN_PWR1|PE_ePWM_CONFIG_EN_PWR0,
} PE_ePWM_EN_PWR_t;

typedef enum {
    PE_ePWM_EN_PWM_NONE   = 0x00U,
    PE_ePWM_EN_PWM_GROUP0 = PE_ePWM_CONFIG_EN_PWM0,
    PE_ePWM_EN_PWM_GROUP1 = PE_ePWM_CONFIG_EN_PWM1,
    PE_ePWM_EN_PWM_ALL    = PE_ePWM_CONFIG_EN_PWM1|PE_ePWM_CONFIG_EN_PWM0,
} PE_ePWM_EN_PWM_t;

typedef enum {
    PE_ePWM_CHANNEL_0 = 0x00U,
    PE_ePWM_CHANNEL_1 = 0x01U,
    PE_ePWM_CHANNEL_2 = 0x02U,
    PE_ePWM_CHANNEL_3 = 0x03U,
    PE_ePWM_CHANNEL_4 = 0x04U,
    PE_ePWM_CHANNEL_5 = 0x05U,
    PE_ePWM_CHANNEL_6 = 0x06U,
    PE_ePWM_CHANNEL_7 = 0x07U,
} PE_ePWM_CHANNEL_N_t;

//TODO add function for update channel state depends on requests
typedef struct {
    uint16_t source;
    uint16_t target;
    uint16_t step;
    uint16_t min;
    uint16_t max;
} PE_ePWM_channel_t;

typedef struct {
    PE_ePWM_channel_t channels[8];
    uint8_t  cmd;
    uint8_t  reg;
    uint8_t  registers[4];
    uint16_t pulses[8];
    uint16_t periods[8];
    uint16_t min[8];//TODO remove
    uint16_t max[8];//TODO remove
} PE_ePWM_device_t;

typedef struct {} PE_ePWM_remote_t; // <-- for control pwm driver

typedef struct {
    uint8_t cmd;
    uint8_t reg;
    void (*read) (uint8_t addr, uint8_t *data, uint8_t size);
    void (*send) (uint8_t addr, uint8_t *data, uint8_t size);
} PE_ePWM_t;

/* Exported function prototypes --------------------------------------------- */
/* Exported variables --------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

void PE_ePWM_setEnabledPWM(PE_ePWM_t *pwm, PE_ePWM_BIT_t value, PE_ePWM_EN_PWM_t mask);
void PE_ePWM_setEnabledPWR(PE_ePWM_t *pwm, PE_ePWM_BIT_t value, PE_ePWM_EN_PWR_t mask);

void PE_ePWM_setPulseEN(PE_ePWM_t *pwm, PE_ePWM_BIT_t value, uint8_t mask);
void PE_ePWM_setPulseClock(PE_ePWM_t *pwm, uint16_t value);
void PE_ePWM_setPulseReset(PE_ePWM_t *pwm, uint16_t value);

void PE_ePWM_setPulse(PE_ePWM_t *pwm, PE_ePWM_CHANNEL_N_t channel, uint16_t value);
void PE_ePWM_setAngle(PE_ePWM_t *pwm, PE_ePWM_CHANNEL_N_t channel, uint16_t value);


//TODO this is draft
void PE_ePWM_onRequest(PE_ePWM_device_t *pwm, uint8_t **data, uint8_t *size);

#ifdef __cplusplus
}
#endif

#endif //PE_ePWM_H
