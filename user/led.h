//
// Created by RenJie on 2018/11/26 0026 15:34.
//

#ifndef RAINWIPER_LED_H
#define RAINWIPER_LED_H

#include "main.h"

#define LED_ON()   GPIO_ResetBits(GPIOC , GPIO_Pin_13)
#define LED_OFF()  GPIO_SetBits(GPIOC , GPIO_Pin_13)
#define LED_REV()  GPIO_Write(GPIOC , GPIO_ReadOutputData(GPIOC) ^ GPIO_Pin_13)

void LED_Init(void);
void LED_Flash(void);

#endif //RAINWIPER_LED_H
