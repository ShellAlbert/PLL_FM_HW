

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

	//initial low level board.
	zboard_low_init();
	printf("FlashLight USART0!\n");

	//Tasks schedule based on Timer.
	ztask_start();

	while (1) {
		/* turn on led2, turn off led5 */
		zled_toggle(1);
		zled_toggle(2);
		delay_1ms(1000);
		ztask_schedule();
	}
}


