//main entry for Project FlashLight
//Feburary 15,2022
//By YantaiElectrician
#include "gd32f30x.h"
#include "systick.h"
#include <stdio.h>
#include "board_gd32f303rgt6.h"
#include "ztask_schedule.h"
int main(void)
{
    systick_config();
	//initial LEDs.
	zled_init(LED1);
    zled_init(LED2);
	
	//initial KEYs.
	zkey_init(KEY_DAY_NIGHT, KEY_MODE_EXTI);
	zkey_init(KEY_CON_FLASH, KEY_MODE_EXTI);
	
	//initial COMs.
	zcom_init(USART0);
	zcom_init(USART1);
	zcom_init(USART2);
	zcom_init(UART3);
	zcom_init(UART4);
	printf("FlashLight USART0!\n");
	
	//Tasks schedule based on Timer.
	ztask_start();
    while(1){
        /* turn on led2, turn off led5 */
        zled_toggle(LED1);
        zled_toggle(LED2);
        delay_1ms(1000);
		ztask_schedule();
    }
}
