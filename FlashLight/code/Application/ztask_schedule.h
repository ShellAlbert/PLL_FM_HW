

//file: ztask_schedule.h
//funtion: task schedule based on Timer.
//date: Feburary 15,2022
//author: by YantaiElectrician
#ifndef _ZSY_TASK_SCHEDULE_H__
#define _ZSY_TASK_SCHEDULE_H__

//to compatible with c++ compiler.
#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
	typedef struct _ZTASK_COMPONENTS__ {
		uint8_t 		iRunFlag;					//1:run,0:stop.
		uint32_t		iTimerCnt;					//current timer count value.
		uint32_t		iTimerCntReload;			//internal running reload value.
		void(*TaskHook) (void);
	} ZTASK_COMPONENTS;


	//define task list clearly to get ZTASK_MAX value.
	typedef enum _ZTASK_LIST__ {
		ZTASK_LED_STATUS, 
		ZTASK_KEY_SCAN, 
		ZTASK_MCU_ADC, 
		ZTASK_I2C_ADC, 
		ZTASK_USART0,
		ZTASK_USART1,
		ZTASK_USART2,
		ZTASK_UART3,
		ZTASK_UART4,
		ZTASK_MAX
	} ZTASK_LIST;


	//should be called in Timer Interrupt Service Routine(ISR).
	//if the Timer is 1ms,then the frequency of execution is 1ms.
	//frequency ISR accompany with low performance.
	//more time with ISR,low realtime performance.
	extern void ztask_remarks_ISR(void);
	extern void ztask_start(void);
	extern void ztask_schedule(void);

	extern void ztask_led_status(void);
	extern void ztask_key_scan(void);
	extern void ztask_mcu_adc(void);
	extern void ztask_i2c_adc(void);
	extern void ztask_usart0(void);
	extern void ztask_usart1(void);
	extern void ztask_usart2(void);
	extern void ztask_uart3(void);
	extern void ztask_uart4(void);
	extern ZTASK_COMPONENTS ztask_comps[ZTASK_MAX];




	//to compatible with c++ compiler.
#ifdef __cplusplus
}


#endif

#endif //_ZSY_TASK_SCHEDULE_H__

