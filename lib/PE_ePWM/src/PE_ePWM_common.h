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
//TODO immediate update timers if pwm config changed
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
#define PE_ePWM_REG_NONE             0xFFU

/** CONFIG_MODE bits **********************************************************/

#define PE_ePWM_CONFIG_EN_CH_0_Pos  (0x0U)
#define PE_ePWM_CONFIG_EN_CH_0_Msk  (0x1U << PE_ePWM_CONFIG_EN_CH_0_Pos)

#define PE_ePWM_CONFIG_EN_CH_1_Pos  (0x1U)
#define PE_ePWM_CONFIG_EN_CH_1_Msk  (0x1U << PE_ePWM_CONFIG_EN_CH_1_Pos)

#define PE_ePWM_CONFIG_EN_CH_2_Pos  (0x2U)
#define PE_ePWM_CONFIG_EN_CH_2_Msk  (0x1U << PE_ePWM_CONFIG_EN_CH_2_Pos)

#define PE_ePWM_CONFIG_EN_CH_3_Pos  (0x3U)
#define PE_ePWM_CONFIG_EN_CH_3_Msk  (0x1U << PE_ePWM_CONFIG_EN_CH_3_Pos)

#define PE_ePWM_CONFIG_EN_CH_4_Pos  (0x4U)
#define PE_ePWM_CONFIG_EN_CH_4_Msk  (0x1U << PE_ePWM_CONFIG_EN_CH_4_Pos)

#define PE_ePWM_CONFIG_EN_CH_5_Pos  (0x5U)
#define PE_ePWM_CONFIG_EN_CH_5_Msk  (0x1U << PE_ePWM_CONFIG_EN_CH_5_Pos)

#define PE_ePWM_CONFIG_EN_CH_6_Pos  (0x6U)
#define PE_ePWM_CONFIG_EN_CH_6_Msk  (0x1U << PE_ePWM_CONFIG_EN_CH_6_Pos)

#define PE_ePWM_CONFIG_EN_CH_7_Pos  (0x7U)
#define PE_ePWM_CONFIG_EN_CH_7_Msk  (0x1U << PE_ePWM_CONFIG_EN_CH_7_Pos)

#define PE_ePWM_CONFIG_SERVO_Pos    (0x8U)
#define PE_ePWM_CONFIG_SERVO_Msk    (0x1U << PE_ePWM_CONFIG_SERVO_Pos)

#define PE_ePWM_CONFIG_EN_PWR_Pos   (0x9U)
#define PE_ePWM_CONFIG_EN_PWR_Msk   (0x1U << PE_ePWM_CONFIG_EN_PWR_Pos)

#define PE_ePWM_CONFIG_EN_PWM_0_Pos (0xAU)
#define PE_ePWM_CONFIG_EN_PWM_0_Msk (0x1U << PE_ePWM_CONFIG_EN_PWM_0_Pos)

#define PE_ePWM_CONFIG_EN_PWM_1_Pos (0xBU)
#define PE_ePWM_CONFIG_EN_PWM_1_Msk (0x1U << PE_ePWM_CONFIG_EN_PWM_1_Pos)

#define PE_ePWM_CONFIG_RESERVED_0   (0xCU)
#define PE_ePWM_CONFIG_RESERVED_1   (0xDU)
#define PE_ePWM_CONFIG_RESERVED_2   (0xEU)
#define PE_ePWM_CONFIG_RESERVED_3   (0xFU)

/* Exported types ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported function prototypes --------------------------------------------- */
/* Exported variables --------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

uint8_t address = PE_ePWM_REG_NONE;
uint16_t registers[PE_ePWM_REG_CH7_SPEED];

// Trigger on receive completed
void onReceive(uint8_t *data, uint8_t size)
{
    address = *data;

    if (size > 1) {
        uint8_t offset = 1;
        uint8_t length = size - 1;

        // write register in autoincrement mode
        while (length > 2) {
            registers[address] = (uint16_t) *(data + offset);

            offset += 2;
            length -= 2;
        }
    }
}

// Trigger on data requested
void onRequest(uint8_t *data, uint8_t *size)
{
    if (address) {
        uint8_t offset = 0;

        for (; address < PE_ePWM_REG_CH7_SPEED; address++) {
            *((uint16_t *) (data + offset)) = registers[address];

            offset += 2;
        }

        *size = offset;
    }
}

#ifdef __cplusplus
}
#endif

#endif //PE_ePWM_COMMON_H
