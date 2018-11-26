//
// Created by RenJie on 2018/11/26 0026 17:03.
//

#include "main.h"

uint32_t pulseCount = 0;

void sendPulses(int count) {
    int i = 0;
    while (i++ < count) {
        PWM_ON();
        delay_ms(1);
        PWM_OFF();
        delay_ms(1);
    }
}

void IR_Handle() {
    pulseCount = 0;
    sendPulses(50);
    PWM_ON();
    if(pulseCount > 5) {
        pulseCount = 0;
        LED_Flash();
        LED_Flash();
    }
}

void EXTI15_10_IRQHandler(void) {
    EXTI_ClearFlag(EXTI_Line12);
    pulseCount ++;
}
