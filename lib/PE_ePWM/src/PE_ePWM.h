/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef PE_ePWM_H
#define PE_ePWM_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/** Instructions **************************************************************/

#define PE_ePWM_CMD_R_REGISTER 0x00U
#define PE_ePWM_CMD_W_REGISTER 0x40U
#define PE_ePWM_CMD_NOP        0xFFU

/** Registers *****************************************************************/

#define PE_ePWM_REG_CONFIG_GET   (0x00U) // <-- R: Get driver config bits
#define PE_ePWM_REG_CONFIG_SET   (0x01U) // <-- W: Set driver config bits
#define PE_ePWM_REG_CONFIG_CLR   (0x02U) // <-- W: Clr driver config bits
#define PE_ePWM_REG_PULSE_EN_GET (0x03U) // <-- R: Get pulse enabled state
#define PE_ePWM_REG_PULSE_EN_SET (0x04U) // <-- W: Set pulse enabled
#define PE_ePWM_REG_PULSE_EN_CLR (0x05U) // <-- W: Set pulse disabled
//TODO config driver mode: pwm/servo
//TODO config power enable/disable for channel group
//TODO value registers

/* Exported macro ------------------------------------------------------------*/

/** CONFIG bits ***************************************************************/

#define PE_ePWM_CONFIG_MODE0_Pos (0x00U)
#define PE_ePWM_CONFIG_MODE0_Msk (0x01U << PE_ePWM_CONFIG_MODE0_Pos)
#define PE_ePWM_CONFIG_MODE0     PE_ePWM_CONFIG_MODE0_Msk

#define PE_ePWM_CONFIG_MODE1_Pos (0x01U)
#define PE_ePWM_CONFIG_MODE1_Msk (0x01U << PE_ePWM_CONFIG_MODE1_Pos)
#define PE_ePWM_CONFIG_MODE1     PE_ePWM_CONFIG_MODE1_Msk

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

/* Exported function prototypes --------------------------------------------- */
/* Exported variables --------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif //PE_ePWM_H
