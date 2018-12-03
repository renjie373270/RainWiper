//
// Created by RenJie on 2018/11/26 0026 17:03.
//

#include "main.h"

uint32_t pulseCount = 0;



void IR_Handle() {
    PWM_ON();
    delay_ms(100);
    if(pulseCount > 5) {
        pulseCount = 0;
//        LED_Flash();
    }
    pulseCount = 0;
    PWM_OFF();
    delay_ms(100);
}

void EXTI15_10_IRQHandler(void) {
    EXTI_ClearFlag(EXTI_Line12);
    pulseCount ++;
}
