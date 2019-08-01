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

//TODO set mode register
//TODO pulse enable/disable register
//TODO power enable/disable register
//TODO value registers

/* Exported macro ------------------------------------------------------------*/
/* Exported function prototypes --------------------------------------------- */
/* Exported variables --------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif //PE_ePWM_H
