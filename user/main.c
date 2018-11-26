#include "main.h"


void AllDeviceInit(void)
{
	SystemInit();
	UserSysTick_Config(72000000);
	LED_Init();
    TIM1_PWM_CH1_Config(72000000, 38000, 0.5);
	IR_EXTI_Init();
}

int main()
{
    AllDeviceInit();
		LED_OFF();
    while(1) {
			
		}
}


void EXTI15_10_IRQHandler(void) {
    EXTI_ClearFlag(EXTI_Line12);
    LED_Flash();
		LED_Flash();
		LED_Flash();
		LED_OFF();
}
