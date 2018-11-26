//
// Created by RenJie on 2018/11/26 0026.
//

#ifndef RAINWIPER_PWM_H
#define RAINWIPER_PWM_H

#include "main.h"


/**
 * 系统频率，pwm频率，占空比
 * */
void TIM1_PWM_CH1_Config(uint32_t systemFreq, uint32_t pwmFreq, float dutyRatio);
void PWM_ON(void);
void PWM_OFF(void);

#endif //RAINWIPER_PWM_H
