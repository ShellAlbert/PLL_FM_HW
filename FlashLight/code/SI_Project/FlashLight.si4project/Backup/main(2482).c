//main entry for Project FlashLight
//Feburary 15,2022
//By YantaiElectrician
#include "gd32f30x.h"
#include "systick.h"
#include <stdio.h>
#include "board_gd32f303rgt6.h"
void ZTaskSchedule();
int main(void)
{
    systick_config();
	//initial LEDs.
	zled_init(LED1);
    zled_init(LED2);

	//Tasks schedule based on Timer.
    while(1){
        /* turn on led2, turn off led5 */
        gd_eval_led_on(LED2);
        gd_eval_led_off(LED5);
        delay_1ms(1000);
		ZTask_Schedule();
    }
}
