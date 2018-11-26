//
// Created by RenJie on 2018/11/26 0026 16:11.
//

#include "exti.h"

void Port_Config() {
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//上拉输入
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void NVIC_Config() {
    EXTI_InitTypeDef EXTI_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource12);//配置PB12为外部中断引脚
    EXTI_InitStructure.EXTI_Line = EXTI_Line12;//外部中断线0
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;//下降沿触发
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;//中断使能
    EXTI_Init(&EXTI_InitStructure);

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//先占优先级占2位，从优先级占2位
    NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;//外部中断10 ~ 15
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;//先占优先级为3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority =  1;//从优先级为1
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

void IR_EXTI_Init() {
    Port_Config();
    NVIC_Config();
}
