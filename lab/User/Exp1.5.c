#include "stm32f10x.h"
#include "IERG3810_KEY.h"
#include "IERG3810_LED.h"
#include "IERG3810_Buzzer.h"


//--Exp0
void Delay(u32 count)
{
	u32 i;
	for(i=0;i<count;i++);
}

int main(void)
{
	IERG3810_KEY_Init();
	IERG3810_LED_Init();
	IERG3810_Buzzer_Init();
	
	while(1)
	{
		Delay(5000);
		if (key2_down) DS0_On;
		else DS0_Off;
		
		key1_update;
		if (key1_press) DS1_toggle;
		
		keyup_update;
		if(keyup_press) Buzzer_toggle;
	}
}
