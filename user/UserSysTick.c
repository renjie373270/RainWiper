//
// Created by RenJie on 2018/11/26 0026 15:39.
//

#include "UserSysTick.h"


void delay_ms(uint32_t x) {
    uint32_t SysTimeVal;
    SysTimeVal = x;
    while(SysTimeVal!=0)
    {
        while(SysTick_GetFlagStatus(SysTick_FLAG_COUNT)!=RESET)
            SysTimeVal--;
    }
}

void UserSysTick_Config(uint32_t systemFreq) {
    SysTick_ITConfig(DISABLE);
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
    SysTick_SetReload(systemFreq / 1000);
    SysTick_CounterCmd(SysTick_Counter_Enable);
}
