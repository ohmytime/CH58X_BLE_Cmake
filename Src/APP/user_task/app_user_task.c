#include "HAL.h"
#include "app_user_task.h"

uint8_t UserLEDTaskID = INVALID_TASK_ID;

uint16_t led_process_event(uint8_t taskID, uint16_t events) {
    // 定时时间到，停止任务
    if (events & USER_LED_TIME_OUT_EVENT) {
        GPIOB_SetBits(GPIO_Pin_21);
        // HAL_TURN_OFF_LED1();
        tmos_stop_task(UserLEDTaskID, TOGGLE_LED_EVENT);

        return (events ^ USER_LED_TIME_OUT_EVENT);
    }
    // 开启转换LED任务
    if (events & TOGGLE_LED_EVENT) {
        GPIOB_InverseBits(GPIO_Pin_21);
        // HAL_TURN_ON_LED1();
        tmos_start_task(taskID, TOGGLE_LED_EVENT, LED_HOLD_TIME);

        return (events ^ TOGGLE_LED_EVENT);
    }
    return 0;
}

void PROCESS_BLE_DATA_HANDLE(uint8_t *data, uint16_t length) {

    if (strstr((const char *)data, "led")) {
        if (data[3] == '1') {
            GPIOB_ModeCfg(GPIO_Pin_21, GPIO_ModeOut_PP_5mA);
            tmos_start_task(UserLEDTaskID, TOGGLE_LED_EVENT, LED_HOLD_TIME);
        } else if (data[3] == '0') {
            tmos_stop_task(UserLEDTaskID, TOGGLE_LED_EVENT);
        }
    }
}

void TMOS_Keypad_init(void) {
    UserLEDTaskID = TMOS_ProcessEventRegister(led_process_event);
}