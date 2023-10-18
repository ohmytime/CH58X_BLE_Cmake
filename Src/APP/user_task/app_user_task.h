#ifndef _USER_TASK_H_
#define _USER_TASK_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "config.h"

#define USER_LED_TIME_OUT_EVENT         (0x0001<<0)
#define TOGGLE_LED_EVENT                (0x0001<<1)

#define  LED_HOLD_TIME          320  // 320 *625us -> 200ms

void TMOS_Keypad_init(void);
void PROCESS_BLE_DATA_HANDLE(uint8_t *data, uint16_t length);

#ifdef __cplusplus
}
#endif

#endif
