//
// Created by RenJie on 2018/11/26 0026 15:34.
//

#include "main.h"

void LED_Init() {
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC , &GPIO_InitStructure);
}

void LED_Flash() {
    LED_REV();
    delay_ms(200);
    LED_REV();
    delay_ms(200);
}
