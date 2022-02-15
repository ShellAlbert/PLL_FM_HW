
//file: ztask_schedule.c
//funtion: task schedule based on Timer.
//date: Feburary 15,2022
//author: by YantaiElectrician
#include "ztask_schedule.h"
ZTASK_COMPONENTS ztask_comps[ZTASK_MAX] = {
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
};

//should be called in Timer Interrupt Service Routine(ISR).
//if the Timer is 1ms,then the frequency of execution is 1ms.
//frequency ISR accompany with low performance.
//more time within ISR,low realtime performance we get.
void ztask_remarks_ISR(void)
{
	uint8_t			i;
	//loop to process each task.
	for (i = 0; i < ZTASK_MAX; i++) {
		if (ztask_comps[i].iTimerCnt > 0) {
			ztask_comps[i].iTimerCnt--;

			//reload timer count to execute again.
			if (ztask_comps[i].iTimerCnt == 0) {
				ztask_comps[i].iTimerCnt = ztask_comps[i].iTimerCntReload;
				ztask_comps[i].iRunFlag = 1;			//can be scheduled again.
			}
		}
	}
}

//should be called in main()/while(1).
void ztask_schedule(void)
{
	uint8_t			i;

	for (i = 0; i < ZTASK_MAX; i++) {
		if (ztask_comps[i].iRunFlag) {
			ztask_comps[i].TaskHook();
			ztask_comps[i].iRunFlag = 1;			//can be scheduled again.
		}
	}
}


void ztask_led_status(void)
{
}


void ztask_key_scan(void)
{
}


void ztask_mcu_adc(void)
{
}
void ztask_i2c_adc(void)
{
}


void ztask_start(void)
{
	uint8_t i;
	for (i = 0; i < ZTASK_MAX; i++) {
		ztask_comps[i].iRunFlag = 1;				//set run flag.
	}
}


