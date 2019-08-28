/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef PE_ePWM_COMMON_H
#define PE_ePWM_COMMON_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

#define PE_ePWM_SERVO_MIN 600
#define PE_ePWM_SERVO_MID 1450
#define PE_ePWM_SERVO_MAX 2300

/** Registers *****************************************************************/

/**
 * Descriptions:
 * All registers are 16bit
 * Write to each register from CH0_MIN increment internal address pointer
 * - CONFIG_PWM_CLOCK and CONFIG_PWM_RESET register values ignored in SERVO mode
 * - *_MIN and *_MAX registers accept pulse width limits for both modes
 * - *_MIN and *_MAX registers in SERVO mode also used for map value range
 * - *_VALUE registers accept pulse width for PWM mode and degree * 10 for SERVO mode
 * - *_SPEED registers accept duration in milliseconds for both modes
 */

#define PE_ePWM_REG_CONFIG_MODE      0x00U
#define PE_ePWM_REG_CONFIG_PWM_CLOCK 0x01U
#define PE_ePWM_REG_CONFIG_PWM_RESET 0x02U
#define PE_ePWM_REG_CH0_MIN          0x20U
#define PE_ePWM_REG_CH0_MAX          0x21U
#define PE_ePWM_REG_CH1_MIN          0x22U
#define PE_ePWM_REG_CH1_MAX          0x23U
#define PE_ePWM_REG_CH2_MIN          0x24U
#define PE_ePWM_REG_CH2_MAX          0x25U
#define PE_ePWM_REG_CH3_MIN          0x26U
#define PE_ePWM_REG_CH3_MAX          0x27U
#define PE_ePWM_REG_CH4_MIN          0x28U
#define PE_ePWM_REG_CH4_MAX          0x29U
#define PE_ePWM_REG_CH5_MIN          0x2AU
#define PE_ePWM_REG_CH5_MAX          0x2BU
#define PE_ePWM_REG_CH6_MIN          0x2CU
#define PE_ePWM_REG_CH6_MAX          0x2DU
#define PE_ePWM_REG_CH7_MIN          0x2EU
#define PE_ePWM_REG_CH7_MAX          0x2FU
#define PE_ePWM_REG_CH0_VALUE        0x20U
#define PE_ePWM_REG_CH0_SPEED        0x21U
#define PE_ePWM_REG_CH1_VALUE        0x22U
#define PE_ePWM_REG_CH1_SPEED        0x23U
#define PE_ePWM_REG_CH2_VALUE        0x24U
#define PE_ePWM_REG_CH2_SPEED        0x25U
#define PE_ePWM_REG_CH3_VALUE        0x26U
#define PE_ePWM_REG_CH3_SPEED        0x27U
#define PE_ePWM_REG_CH4_VALUE        0x28U
#define PE_ePWM_REG_CH4_SPEED        0x29U
#define PE_ePWM_REG_CH5_VALUE        0x2AU
#define PE_ePWM_REG_CH5_SPEED        0x2BU
#define PE_ePWM_REG_CH6_VALUE        0x2CU
#define PE_ePWM_REG_CH6_SPEED        0x2DU
#define PE_ePWM_REG_CH7_VALUE        0x2EU
#define PE_ePWM_REG_CH7_SPEED        0x2FU

/* Exported types ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported function prototypes --------------------------------------------- */
/* Exported variables --------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif //PE_ePWM_COMMON_H
