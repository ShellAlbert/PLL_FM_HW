

//file: main.c
//funtion: main entry for Project FlashLight
//date: Feburary 15,2022
//author: by YantaiElectrician

/*----------------LED*2----------------*/
////LED1,LED2: 0:ON,1:OFF.

/*----------------KEY*15----------------*/
////SGM7SZ14 ( Y=~A) Small Logic Inverter with Schmitt Trigger Input
////There are pull-up resistors in connectors,
////No keys were pressed, IO got 1.
////Keys were pressed IO got 0.
////Since the schematic add a logical buffer, so we get true value table below.
////No keys were pressed, IO got 0.
////Keys were pressed, IO got 1.
////So EXTI were configured to Rising Edge Trigger.

/*----------------UART*5----------------*/
////USART0: For Debug TTL-USB. (3.3V TTL Level)
////USART1: To communicate with Laser Distance Module. (RS422,Full duplex)
////USART2: To communicate with Display module. (3.3V TTL Level)
////UART3: To communicate with WiFi-UART module. (3.3V TTL Level)
////UART4: To communicate with Laser Module. (3.3V TTL Level)

/*----------------I2C*1----------------*/
//SPI*1
//ADC*1
//DAC*2

/*----------------TIMER*2----------------*/
////TIMER7_CH0:PC6, TIMER7_CH1:PC7
////TIMER3_CH0:PB6, TIMER3_CH1:PB7
//DMA0-Channel0:ADC0
#include "gd32f30x.h"
#include "systick.h"
#include <stdio.h>
#include "board_gd32f303rgt6.h"
#include "ztask_schedule.h"
static void PowerOnDelay(int32_t delay)
{
	volatile int32_t ms = 0;

	while (delay--) {
		for (ms = 0; ms < 0xffff; ms++)
			;
	}
}


int main(void)
{
	//configure clock.
	systick_config();

	//give some time to JTAG connected to JLink.
	//if we disable JTAG and SWD and no much waiting time here,
	//then we cannot download firmware anymore.
	PowerOnDelay(10);

	//initial low level board.
	//includes all peripheral devices.
	zboard_low_init();

	printf("FlashLight USART0!\n");
	//Tasks schedule based on Timer.
	ztask_start();

	//infite-loop to schedule tasks.
	while (1) {
		ztask_schedule();
	}

	return 0;
}




