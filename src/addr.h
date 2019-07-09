/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ADDR_H
#define __ADDR_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include "main.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported function prototypes --------------------------------------------- */
/* Exported variables --------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

void MX_ADDR_Init(void);

uint8_t MX_ADDR_Read(void);

#ifdef __cplusplus
}
#endif

#endif //__ADDR_H
