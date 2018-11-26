#include "stm32f10x.h"
#include "main.h"

/*
#define LED_ON()   GPIO_ResetBits(GPIOC , GPIO_Pin_13)
#define LED_OFF()  GPIO_SetBits(GPIOC , GPIO_Pin_13)
#define LED_REV()  GPIO_Write(GPIOC , GPIO_ReadOutputData(GPIOC) ^ GPIO_Pin_13)

#define IR_Transmit_1_ON()  GPIO_ResetBits(GPIOA , GPIO_Pin_0)
#define IR_Transmit_2_ON()  GPIO_ResetBits(GPIOA , GPIO_Pin_1)
#define IR_Transmit_3_ON()  GPIO_ResetBits(GPIOA , GPIO_Pin_2)
#define IR_Transmit_4_ON()  GPIO_ResetBits(GPIOA , GPIO_Pin_3)
#define IR_Transmit_5_ON()  GPIO_ResetBits(GPIOA , GPIO_Pin_4)
#define IR_Transmit_6_ON()  GPIO_ResetBits(GPIOA , GPIO_Pin_5)

#define IR_Transmit_1_OFF()  GPIO_SetBits(GPIOA , GPIO_Pin_0)
#define IR_Transmit_2_OFF()  GPIO_SetBits(GPIOA , GPIO_Pin_1)
#define IR_Transmit_3_OFF()  GPIO_SetBits(GPIOA , GPIO_Pin_2)
#define IR_Transmit_4_OFF()  GPIO_SetBits(GPIOA , GPIO_Pin_3)
#define IR_Transmit_5_OFF()  GPIO_SetBits(GPIOA , GPIO_Pin_4)
#define IR_Transmit_6_OFF()  GPIO_SetBits(GPIOA , GPIO_Pin_5)

#define IR_Transmit_1_REV()  GPIO_Write(GPIOA , GPIO_ReadOutputData(GPIOA) ^ GPIO_Pin_0)
#define IR_Transmit_2_REV()  GPIO_Write(GPIOA , GPIO_ReadOutputData(GPIOA) ^ GPIO_Pin_1)
#define IR_Transmit_3_REV()  GPIO_Write(GPIOA , GPIO_ReadOutputData(GPIOA) ^ GPIO_Pin_2)
#define IR_Transmit_4_REV()  GPIO_Write(GPIOA , GPIO_ReadOutputData(GPIOA) ^ GPIO_Pin_3)
#define IR_Transmit_5_REV()  GPIO_Write(GPIOA , GPIO_ReadOutputData(GPIOA) ^ GPIO_Pin_4)
#define IR_Transmit_6_REV()  GPIO_Write(GPIOA , GPIO_ReadOutputData(GPIOA) ^ GPIO_Pin_5)


void delayms(uint32_t x) {	
	uint32_t SysTimeVal;
	SysTimeVal = x;
	while(SysTimeVal!=0)
	{
		while(SysTick_GetFlagStatus(SysTick_FLAG_COUNT)!=RESET)
		SysTimeVal--;		
	}
}


void delayus(uint32_t x) {
	int i, j;
	for(i = 0; i < x; i++)
	for(j = 0; j < 4; j++);
}

void UserRCC_Config(void)
{
	SystemInit();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
}


void UserSysTick_Config(void)
{
	SysTick_ITConfig(DISABLE);
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
	SysTick_SetReload(72000);	
	SysTick_CounterCmd(SysTick_Counter_Enable);		
}


void UserGPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC , &GPIO_InitStructure);	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;	
	GPIO_Init(GPIOA , &GPIO_InitStructure);
}


void AllDeviceInit(void)
{
	UserRCC_Config();
	UserSysTick_Config();
	UserGPIO_Config();
}

void IR_1_Send() {
	uint32_t i;
	for(i = 0; i < 10000; i++) {
		delayus(23);		
		IR_Transmit_1_REV();
	}		
	IR_Transmit_1_OFF();
}

void IR_2_Send() {
	uint32_t i;
	for(i = 0; i < 10000; i++) {
		delayus(23);		
		IR_Transmit_2_REV();
	}		
	IR_Transmit_2_OFF();
}

void IR_3_Send() {
	uint32_t i;
	for(i = 0; i < 10000; i++) {
		delayus(23);		
		IR_Transmit_3_REV();
	}		
	IR_Transmit_3_OFF();
}

void IR_4_Send() {
	uint32_t i;
	for(i = 0; i < 10000; i++) {
		delayus(23);		
		IR_Transmit_4_REV();
	}		
	IR_Transmit_4_OFF();
}

void IR_5_Send() {
	uint32_t i;
	for(i = 0; i < 10000; i++) {
		delayus(23);		
		IR_Transmit_5_REV();
	}		
	IR_Transmit_5_OFF();
}

void IR_6_Send() {
	uint32_t i;
	for(i = 0; i < 10000; i++) {
		delayus(23);		
		IR_Transmit_6_REV();
	}		
	IR_Transmit_6_OFF();
}

void LEDFlash() {
	int i;
	for(i = 0; i < 10; i++) {
		delayms(100);
		LED_REV();
	}		
	LED_OFF();
}

int main(void)
{
	AllDeviceInit();
	while(1)
	{				
		//LEDFlash();
		IR_1_Send();
		IR_2_Send();
		IR_3_Send();
		IR_4_Send();
		IR_5_Send();
		IR_6_Send();
	}
}
*/

void UserRCC_Config(void)
{
	SystemInit();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
}


int main()
{
	UserRCC_Config();
    TIM1_PWM_CH1_Config(72000000, 38000, 0.5);
}

