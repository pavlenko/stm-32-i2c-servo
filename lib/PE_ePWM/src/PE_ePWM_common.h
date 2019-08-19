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

//TODO change logic to all registers are 16bit, pulse and duration must be alternated (чередоваться)
//TODO move registers code here & create reg list with possibility autoincrement addr for allow write multiple channel values???

/* Exported types ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported function prototypes --------------------------------------------- */
/* Exported variables --------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif //PE_ePWM_COMMON_H
