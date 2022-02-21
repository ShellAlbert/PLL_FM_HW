

//file: ztask_schedule.c
//funtion: task schedule based on Timer.
//date: Feburary 15,2022
//author: by YantaiElectrician
#include "ztask_schedule.h"
#include "board_gd32f303rgt6.h"
#include <string.h>
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
	//less to take cpu time as soon as possible.
	//high performance means run fast!
	zled_toggle(1);
	zled_toggle(2);
}


void ztask_key_scan(void)
{
	uint8_t 		i;

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
}


void ztask_i2c_adc(void)
{
}


void ztask_usart0(void)
{
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
			sprintf((char*)gBrdFlashLight.sUsart0.txbuffer, "%s", "\n\rUSART interrupt test\n\r");
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

}


void ztask_usart2(void)
{

}


void ztask_uart3(void)
{

}


void ztask_uart4(void)
{

}


void ztask_start(void)
{
	uint8_t 		i;

	for (i = 0; i < ZTASK_MAX; i++) {
		ztask_comps[i].iRunFlag = 1;				//set run flag.
	}
}


