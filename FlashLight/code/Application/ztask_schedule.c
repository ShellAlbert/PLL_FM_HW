

//file: ztask_schedule.c
//funtion: task schedule based on Timer.
//date: Feburary 15,2022
//author: by YantaiElectrician
#include "ztask_schedule.h"
#include "board_gd32f303rgt6.h"
#include <string.h>
//Timer3 to output pwm to drive brush DC motor.
extern void ztimer3_bdcm_init(void);
//Timer7 to output pwm to drive brush DC motor.
extern void ztimer7_bdcm_init(void);


ZTASK_COMPONENTS ztask_comps[ZTASK_MAX] =
{
	//led status task.
	{
		0, 60, 60, ztask_led_status
	},

	//key scan task.
	{
		0, 100, 100, ztask_key_scan
	},

	//mcu internal adc task.
	{
		0, 500, 500, ztask_mcu_adc
	},

	//i2c bus adc task.
	{
		0, 500, 500, ztask_i2c_adc
	},

	//usart0 task.
	{
		0, 200, 200, ztask_usart0
	},

	//usart1 task.
	{
		0, 200, 200, ztask_usart1
	},

	//usart2 task.
	{
		0, 200, 200, ztask_usart2
	},

	//usart3 task.
	{
		0, 200, 200, ztask_uart3
	},

	//usart4 task.
	{
		0, 200, 200, ztask_uart4
	},
};


//should be called in Timer Interrupt Service Routine(ISR).
//if the Timer is 1ms,then the frequency of execution is 1ms.
//frequency ISR accompany with low performance.
//more time within ISR,low realtime performance we get.
void ztask_remarks_ISR(void)
{
	uint8_t 		i;

	//loop to process each task.
	for (i = 0; i < ZTASK_MAX; i++) {
		if (ztask_comps[i].iTimerCnt > 0) {
			ztask_comps[i].iTimerCnt--;

			//reload timer count to execute again.
			if (ztask_comps[i].iTimerCnt == 0) {
				ztask_comps[i].iTimerCnt = ztask_comps[i].iTimerCntReload;
				ztask_comps[i].iRunFlag = 1;		//can be scheduled again.
			}
		}
	}
}


//should be called in main()/while(1).
void ztask_schedule(void)
{
	uint8_t 		i;

	for (i = 0; i < ZTASK_MAX; i++) {
		if (ztask_comps[i].iRunFlag) {
			ztask_comps[i].TaskHook();
			ztask_comps[i].iRunFlag = 1;			//can be scheduled again.
		}
	}
}


void ztask_led_status(void)
{
	printf("\r\n1.ztask_led_status()");

	//less to take cpu time as soon as possible.
	//high performance means run fast!
	gpio_bit_set(GPIOA, GPIO_PIN_15);
	delay_1ms(100);
	gpio_bit_reset(GPIOA, GPIO_PIN_15);
	delay_1ms(100);
}


void ztask_key_scan(void)
{
	uint8_t 		i;
	printf("\r\n2.ztask_key_scan()");

	for (i = 0; i < KEY_MAX; i++) {
		switch (i)
		{
			case KEY_DAY_NIGHT:
				if (gBrdFlashLight.iKey[KEY_DAY_NIGHT]) {
					//KEY_DAY_NIGHT was pressed.
					//to do something here.
					printf("KEY_DAY_NIGHT\n");

					//reset flag.
					gBrdFlashLight.iKey[KEY_DAY_NIGHT] = 0;
				}

				break;

			case KEY_CON_FLASH:
				if (gBrdFlashLight.iKey[KEY_CON_FLASH]) {
					//KEY_CON_FLASH was pressed.
					//to do something here.
					printf("KEY_CON_FLASH\n");

					//reset flag.
					gBrdFlashLight.iKey[KEY_CON_FLASH] = 0;
				}

				break;

			case KEY_UP:
				if (gBrdFlashLight.iKey[KEY_UP]) {
					//KEY_UP was pressed.
					//to do something here.
					printf("KEY_UP\n");

					//reset flag.
					gBrdFlashLight.iKey[KEY_UP] = 0;
				}

				break;

			case KEY_DOWN:
				if (gBrdFlashLight.iKey[KEY_DOWN]) {
					//KEY_DOWN was pressed.
					//to do something here.
					printf("KEY_DOWN\n");

					//reset flag.
					gBrdFlashLight.iKey[KEY_DOWN] = 0;
				}

				break;

			case KEY_LEFT:
				if (gBrdFlashLight.iKey[KEY_LEFT]) {
					//KEY_LEFT was pressed.
					//to do something here.
					printf("KEY_LEFT\n");

					//reset flag.
					gBrdFlashLight.iKey[KEY_LEFT] = 0;
				}

				break;

			case KEY_RIGHT:
				if (gBrdFlashLight.iKey[KEY_RIGHT]) {
					//KEY_RIGHT was pressed.
					//to do something here.
					printf("KEY_RIGHT\n");

					//reset flag.
					gBrdFlashLight.iKey[KEY_RIGHT] = 0;
				}

				break;

			case KEY_SET:
				if (gBrdFlashLight.iKey[KEY_SET]) {
					//KEY_SET was pressed.
					//to do something here.
					printf("KEY_SET\n");

					//reset flag.
					gBrdFlashLight.iKey[KEY_SET] = 0;
				}

				break;

			case KEY_LASER_MODE1:
				if (gBrdFlashLight.iKey[KEY_LASER_MODE1]) {
					//KEY_LASER_MODE1 was pressed.
					//to do something here.
					printf("KEY_LASER_MODE1\n");

					//reset flag.
					gBrdFlashLight.iKey[KEY_LASER_MODE1] = 0;
				}

				break;

			case KEY_LASER_MODE2:
				if (gBrdFlashLight.iKey[KEY_LASER_MODE2]) {
					//KEY_LASER_MODE2 was pressed.
					//to do something here.
					printf("KEY_LASER_MODE2\n");

					//reset flag.
					gBrdFlashLight.iKey[KEY_LASER_MODE2] = 0;
				}

				break;

			case KEY_LASER_MODE3:
				if (gBrdFlashLight.iKey[KEY_LASER_MODE3]) {
					//KEY_LASER_MODE3 was pressed.
					//to do something here.
					printf("KEY_LASER_MODE3\n");

					//reset flag.
					gBrdFlashLight.iKey[KEY_LASER_MODE3] = 0;
				}

				break;

			case KEY_LASER_MODE4:
				if (gBrdFlashLight.iKey[KEY_LASER_MODE4]) {
					//KEY_LASER_MODE4 was pressed.
					//to do something here.
					printf("KEY_LASER_MODE4\n");

					//reset flag.
					gBrdFlashLight.iKey[KEY_LASER_MODE4] = 0;
				}

				break;

			case KEY_FL_ADD:
				if (gBrdFlashLight.iKey[KEY_FL_ADD]) {
					//KEY_FL_ADD was pressed.
					//to do something here.
					printf("KEY_FL_ADD\n");

					//reset flag.
					gBrdFlashLight.iKey[KEY_FL_ADD] = 0;
				}

				break;

			case KEY_FL_SUB:
				if (gBrdFlashLight.iKey[KEY_FL_SUB]) {
					//KEY_FL_SUB was pressed.
					//to do something here.
					printf("KEY_FL_SUB\n");
					//Timer3 to output pwm to drive brush DC motor.
					ztimer3_bdcm_init();

					//reset flag.
					gBrdFlashLight.iKey[KEY_FL_SUB] = 0;
				}

				break;

			case KEY_SHOT_SW1:
				if (gBrdFlashLight.iKey[KEY_SHOT_SW1]) {
					//KEY_SHOT_SW1 was pressed.
					//to do something here.
					printf("KEY_SHOT_SW1\n");

					//reset flag.
					gBrdFlashLight.iKey[KEY_SHOT_SW1] = 0;
				}

				break;

			case KEY_SHOT_SW2:
				if (gBrdFlashLight.iKey[KEY_SHOT_SW2]) {
					//KEY_SHOT_SW2 was pressed.
					//to do something here.
					printf("KEY_SHOT_SW2\n");
					//Timer7 to output pwm to drive brush DC motor.
					ztimer7_bdcm_init();
					//reset flag.
					gBrdFlashLight.iKey[KEY_SHOT_SW2] = 0;
				}

				break;

			default:
				break;
		}
	}
}


void ztask_mcu_adc(void)
{
	printf("\r\n3.ztask_mcu_adc()");
	if (gBrdFlashLight.iDMA0Finished) {
		int 			i;
		uint32_t		iVoltageSum[4];
		float			iVoltageAverage[4];
		gBrdFlashLight.iDMA0Finished = 0;

		memset(iVoltageSum, 0, sizeof(iVoltageSum));

		for (i = 0; i < 4 * 50; i += 4) {
			iVoltageSum[0]		+= gBrdFlashLight.iMCUADC[i + 0];
			iVoltageSum[1]		+= gBrdFlashLight.iMCUADC[i + 1];
			iVoltageSum[2]		+= gBrdFlashLight.iMCUADC[i + 2];
			iVoltageSum[3]		+= gBrdFlashLight.iMCUADC[i + 3];
		}

		//ADC012_IN13:PC0
		//Motor#2Current,driven by TIMER3(on PCB Right side)
		//Current*0.2R => Gain=(1+162k/10k)=17.2
		//Current*0.2R*17.2=ADC_Voltage
		//Current=ADC_Voltage/17.2/0.2R
		//ADC_Voltage=ADC_Sample/2^12*3.3V
		iVoltageAverage[0] 	= iVoltageSum[0] / 50.0 / 4096.0 * 3.3 / 3.44;
		
		//ADC012_IN12:PC1
		//Motor#1Current,driven by TIMER7(on PCB Left side)
		//Current*0.2R => Gain=(1+162k/10k)=17.2
		//Current*0.2R*17.2=ADC_Voltage
		//Current=ADC_Voltage/17.2/0.2R
		//ADC_Voltage=ADC_Sample/2^12*3.3V
		iVoltageAverage[1] 	= iVoltageSum[1] / 50.0 / 4096.0 * 3.3 / 3.44;

		//VSYS.
		//[1.62K/(16.2K+1.62K)]*VSYS=3.3V(ADC Full-Scale)
		//VSYS=ADC_Voltage/0.0909
		//ADC_Voltage=ADC_Sample/2^12*3.3V
		iVoltageAverage[2] 	= iVoltageSum[2] / 50.0 / 4096.0 * 3.3 / 0.0909;

		//VDD12_MOTOR.
		//[2.94K/(16.2K+2.94K)]*VDD12_MOTOR=3.3V(ADC Full-Scale)
		//VDD12_MOTOR=ADC_Voltage/0.1536
		//ADC_Voltage=ADC_Sample/2^12*3.3V
		iVoltageAverage[3] 	= iVoltageSum[3] / 50.0 / 4096.0 * 3.3 / 0.1536;

		printf("\r\nRhtMtrCur=%.2fmA,LftMtrCur=%.2fmA,VSYS=%.2fV,VDD12_MOTOR=%.2fV",///<
		iVoltageAverage[0]*1000.0,///<
		iVoltageAverage[1]*1000.0,///<
		iVoltageAverage[2],iVoltageAverage[3]);
		//re-enable Timer1.
		timer_enable(TIMER1);
	}
}


void ztask_i2c_adc(void)
{
	printf("\r\n4.ztask_i2c_adc()");
}


void ztask_usart0(void)
{
	printf("\r\n5.ztask_usart0()");

	switch (gBrdFlashLight.sUsart0.fsm)
	{
		case FSM_PREPARE:
			if (gBrdFlashLight.sUsart0.iDataValid) {
				//go to next state.
				gBrdFlashLight.sUsart0.fsm = FSM_TX;
			}

			break;

		case FSM_TX:
			//tx data should be filled into txbuffer in another place.
			//here is only examples.
			sprintf((char *) gBrdFlashLight.sUsart0.txbuffer, "%s", "\n\rUSART0 interrupt test\n\r");
			gBrdFlashLight.sUsart0.tx_size = ARRAYNUM(gBrdFlashLight.sUsart0.txbuffer) - 1;
			gBrdFlashLight.sUsart0.txcount = 0;
			memset(gBrdFlashLight.sUsart0.rxbuffer, 0, 32);
			gBrdFlashLight.sUsart0.rx_size = 32;
			gBrdFlashLight.sUsart0.rxcount = 0;

			//enable USART TBE(TransmitBufferEmpty) interrupt to start transmit.
			usart_interrupt_enable(USART0, USART_INT_TBE);

			//go to next state.
			gBrdFlashLight.sUsart0.fsm = FSM_TX_WAIT;
			break;

		case FSM_TX_WAIT:
			if (gBrdFlashLight.sUsart0.txcount == gBrdFlashLight.sUsart0.tx_size) {
				//TC=transmission complete.
				if (SET == usart_flag_get(USART0, USART_FLAG_TC)) {
					//go to next state.
					gBrdFlashLight.sUsart0.fsm = FSM_RX;
				}
			}

			break;

		case FSM_RX:
			//enable USART RBNE(ReadBufferNotEmpty) interrupt to start receive.
			usart_interrupt_enable(USART0, USART_INT_RBNE);

			//go to next state.
			gBrdFlashLight.sUsart0.fsm = FSM_RX_WAIT;
			break;

		case FSM_RX_WAIT:
			if (gBrdFlashLight.sUsart0.rxcount == gBrdFlashLight.sUsart0.rx_size) {
				//receive successfully.
				//go to next state.
				gBrdFlashLight.sUsart0.fsm = FSM_DONE;
			}

			break;

		case FSM_DONE:
			//parse data here.
			//...
			//...
			//go to next state.
			gBrdFlashLight.sUsart0.fsm = FSM_PREPARE;
			gBrdFlashLight.sUsart0.iDataValid = 0;
			break;

		default:
			break;
	}
}


void ztask_usart1(void)
{
	printf("\r\n6.ztask_usart1()");

	switch (gBrdFlashLight.sUsart1.fsm)
	{
		case FSM_PREPARE:
			if (gBrdFlashLight.sUsart1.iDataValid) {
				//go to next state.
				gBrdFlashLight.sUsart1.fsm = FSM_TX;
			}

			break;

		case FSM_TX:
			//tx data should be filled into txbuffer in another place.
			//here is only examples.
			sprintf((char *) gBrdFlashLight.sUsart1.txbuffer, "%s", "\n\rUSART1 interrupt test\n\r");
			gBrdFlashLight.sUsart1.tx_size = ARRAYNUM(gBrdFlashLight.sUsart1.txbuffer) - 1;
			gBrdFlashLight.sUsart1.txcount = 0;
			memset(gBrdFlashLight.sUsart1.rxbuffer, 0, 32);
			gBrdFlashLight.sUsart1.rx_size = 32;
			gBrdFlashLight.sUsart1.rxcount = 0;

			//enable USART TBE(TransmitBufferEmpty) interrupt to start transmit.
			usart_interrupt_enable(USART1, USART_INT_TBE);

			//go to next state.
			gBrdFlashLight.sUsart1.fsm = FSM_TX_WAIT;
			break;

		case FSM_TX_WAIT:
			if (gBrdFlashLight.sUsart1.txcount == gBrdFlashLight.sUsart1.tx_size) {
				//TC=transmission complete.
				if (SET == usart_flag_get(USART1, USART_FLAG_TC)) {
					//go to next state.
					gBrdFlashLight.sUsart1.fsm = FSM_RX;
				}
			}

			break;

		case FSM_RX:
			//enable USART RBNE(ReadBufferNotEmpty) interrupt to start receive.
			usart_interrupt_enable(USART1, USART_INT_RBNE);

			//go to next state.
			gBrdFlashLight.sUsart1.fsm = FSM_RX_WAIT;
			break;

		case FSM_RX_WAIT:
			if (gBrdFlashLight.sUsart1.rxcount == gBrdFlashLight.sUsart1.rx_size) {
				//receive successfully.
				//go to next state.
				gBrdFlashLight.sUsart1.fsm = FSM_DONE;
			}

			break;

		case FSM_DONE:
			//parse data here.
			//...
			//...
			//go to next state.
			gBrdFlashLight.sUsart1.fsm = FSM_PREPARE;
			gBrdFlashLight.sUsart1.iDataValid = 0;
			break;

		default:
			break;
	}

}


void ztask_usart2(void)
{
	printf("\r\n7.ztask_usart2()");
}


void ztask_uart3(void)
{
	printf("\r\n8.ztask_uart3()");
}


void ztask_uart4(void)
{
	printf("\r\n9.ztask_uart4()");
}


void ztask_start(void)
{
	uint8_t 		i;

	for (i = 0; i < ZTASK_MAX; i++) {
		ztask_comps[i].iRunFlag = 1;				//set run flag.
	}
}


