#include "main.h"


void UserRCC_Config(void)
{
	SystemInit();
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
}


void AllDeviceInit(void)
{
	UserRCC_Config();
	UserSysTick_Config(72000000);
	LED_Init();
    TIM1_PWM_CH1_Config(72000000, 38000, 0.5);
}


int main()
{
    AllDeviceInit();
    while(1) {
			LED_Flash();
		}
}

