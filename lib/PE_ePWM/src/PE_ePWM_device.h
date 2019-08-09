/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef PE_ePWM_DEVICE_H
#define PE_ePWM_DEVICE_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "PE_ePWM.h"

/* Exported types ------------------------------------------------------------*/

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

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported function prototypes --------------------------------------------- */
/* Exported variables --------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

void PE_ePWM_device_onReceive(PE_ePWM_device_t *pwm, uint8_t *data, uint8_t size);
void PE_ePWM_device_onRequest(PE_ePWM_device_t *pwm, uint8_t *data, uint8_t *size);
void PE_ePWM_device_dispatch(PE_ePWM_device_t *pwm);
void PE_ePWM_device_updateCH(PE_ePWM_device_t *pwm, PE_ePWM_CHANNEL_N_t channel);

#ifdef __cplusplus
}
#endif

#endif //PE_ePWM_DEVICE_H
