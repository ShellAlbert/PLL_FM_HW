

//board configuration file for FlashLight Project.
//Feburary 14,2022
//by Yantai Electrician
#ifndef _ZSY_GD32F303RGT6_H__
#define _ZSY_GD32F303RGT6_H__

//to compatible with c++ compiler.
#ifdef __cplusplus
extern "C"
{
#endif

#include "gd32f30x.h"

	typedef enum {
		LED1 = 0, 
		LED2 = 1, 
	} zled_typedef_enum;


	typedef enum {

		//Day/Night mode switch.
		KEY_DAY_NIGHT = 0, 

		//Continous ON mode/Flash mode.
		KEY_CON_FLASH = 1, 

		//Arrow control keys.
		KEY_UP = 2, 
		KEY_DOWN = 3, 
		KEY_LEFT = 4, 
		KEY_RIGHT = 5, 
		KEY_SET = 6, 

		//Fast to change laser module working mode.
		KEY_LASER_MODE1 = 7, 
		KEY_LASER_MODE2 = 8, 
		KEY_LASER_MODE3 = 9, 
		KEY_LASER_MODE4 = 10, 

		//Manual focal length adjust buttons.
		KEY_FL_ADD = 11, 
		KEY_FL_SUB = 12, 

		//Laser shot trigger switch.
		KEY_SHOT_SW1 = 13, 
		KEY_SHOT_SW2 = 14, 
	} zkey_typedef_enum;


	//board low-level leds.
#define 	LEDn					2U

#define 	LED1_GPIO_PORT			GPIOB
#define 	LED1_PIN				GPIO_PIN_3
#define 	LED1_GPIO_CLK			RCU_GPIOB

#define 	LED2_GPIO_PORT			GPIOA
#define 	LED2_PIN				GPIO_PIN_15
#define 	LED2_GPIO_CLK			RCU_GPIOA

	//board low-level keys.
#define 	KEYn					15U

	//Day/Night mode switch key.
#define 	KEY_DAY_NIGHT_PORT		GPIOA
#define 	KEY_DAY_NIGHT_PIN		GPIO_PIN_1
#define 	KEY_DAY_NIGHT_CLK		RCU_GPIOA
#define 	KEY_DAY_NIGHT_EXTI_LINE EXTI_1
#define 	KEY_DAY_NIGHT_EXTI_PORT_SOURCE GPIO_PORT_SOURCE_GPIOA
#define 	KEY_DAY_NIGHT_EXTI_PIN_SOURCE GPIO_PIN_SOURCE_1
#define 	KEY_DAY_NIGHT_EXTI_IRQn EXTI1_IRQn

	//Continous ON mode/Flash mode switch key.
#define 	KEY_CON_FLASH_PORT		GPIOB
#define 	KEY_CON_FLASH_PIN		GPIO_PIN_4
#define 	KEY_CON_FLASH_CLK		RCU_GPIOB
#define 	KEY_CON_FLASH_EXTI_LINE EXTI_4
#define 	KEY_CON_FLASH_EXTI_PORT_SOURCE GPIO_PORT_SOURCE_GPIOB
#define 	KEY_CON_FLASH_EXTI_PIN_SOURCE GPIO_PIN_SOURCE_4
#define 	KEY_CON_FLASH_EXTI_IRQn EXTI4_IRQn

	//Arrow control keys.
	//UP_SW:PC4
#define 	KEY_UP_PORT 			GPIOC
#define 	KEY_UP_PIN				GPIO_PIN_4
#define 	KEY_UP_CLK				RCU_GPIOC
#define 	KEY_UP_EXTI_LINE		EXTI_4
#define 	KEY_UP_EXTI_PORT_SOURCE GPIO_PORT_SOURCE_GPIOC
#define 	KEY_UP_EXTI_PIN_SOURCE	GPIO_PIN_SOURCE_4
#define 	KEY_UP_EXTI_IRQn		EXTI4_IRQn

	//DOWN_SW:PC5
#define 	KEY_DOWN_PORT			GPIOC
#define 	KEY_DOWN_PIN			GPIO_PIN_5
#define 	KEY_DOWN_CLK			RCU_GPIOC
#define 	KEY_DOWN_EXTI_LINE		EXTI_5
#define 	KEY_DOWN_EXTI_PORT_SOURCE GPIO_PORT_SOURCE_GPIOC
#define 	KEY_DOWN_EXTI_PIN_SOURCE GPIO_PIN_SOURCE_5
#define 	KEY_DOWN_EXTI_IRQn		EXTI5_9_IRQn

	//LEFT_SW:PB0
#define 	KEY_LEFT_PORT			GPIOB
#define 	KEY_LEFT_PIN			GPIO_PIN_0
#define 	KEY_LEFT_CLK			RCU_GPIOB
#define 	KEY_LEFT_EXTI_LINE		EXTI_0
#define 	KEY_LEFT_EXTI_PORT_SOURCE GPIO_PORT_SOURCE_GPIOB
#define 	KEY_LEFT_EXTI_PIN_SOURCE GPIO_PIN_SOURCE_0
#define 	KEY_LEFT_EXTI_IRQn		EXTI0_IRQn

	//RIGHT_SW:PB1
#define 	KEY_RIGHT_PORT			GPIOB
#define 	KEY_RIGHT_PIN			GPIO_PIN_1
#define 	KEY_RIGHT_CLK			RCU_GPIOB
#define 	KEY_RIGHT_EXTI_LINE 	EXTI_1
#define 	KEY_RIGHT_EXTI_PORT_SOURCE GPIO_PORT_SOURCE_GPIOB
#define 	KEY_RIGHT_EXTI_PIN_SOURCE GPIO_PIN_SOURCE_1
#define 	KEY_RIGHT_EXTI_IRQn 	EXTI1_IRQn

	//SET_SW:PB5
#define 	KEY_SET_PORT			GPIOB
#define 	KEY_SET_PIN 			GPIO_PIN_5
#define 	KEY_SET_CLK 			RCU_GPIOB
#define 	KEY_SET_EXTI_LINE		EXTI_5
#define 	KEY_SET_EXTI_PORT_SOURCE GPIO_PORT_SOURCE_GPIOB
#define 	KEY_SET_EXTI_PIN_SOURCE GPIO_PIN_SOURCE_5
#define 	KEY_SET_EXTI_IRQn		EXTI5_9_IRQn

	//LASER_MODE1:PA6
#define 	KEY_LASER_MODE1_PORT	GPIOA
#define 	KEY_LASER_MODE1_PIN 	GPIO_PIN_6
#define 	KEY_LASER_MODE1_CLK 	RCU_GPIOA
#define 	KEY_LASER_MODE1_EXTI_LINE EXTI_6
#define 	KEY_LASER_MODE1_EXTI_PORT_SOURCE GPIO_PORT_SOURCE_GPIOA
#define 	KEY_LASER_MODE1_EXTI_PIN_SOURCE GPIO_PIN_SOURCE_6
#define 	KEY_LASER_MODE1_EXTI_IRQn EXTI5_9_IRQn

	//LASER_MODE2:PC13
#define 	KEY_LASER_MODE2_PORT	GPIOC
#define 	KEY_LASER_MODE2_PIN 	GPIO_PIN_13
#define 	KEY_LASER_MODE2_CLK 	RCU_GPIOC
#define 	KEY_LASER_MODE2_EXTI_LINE EXTI_13
#define 	KEY_LASER_MODE2_EXTI_PORT_SOURCE GPIO_PORT_SOURCE_GPIOC
#define 	KEY_LASER_MODE2_EXTI_PIN_SOURCE GPIO_PIN_SOURCE_13
#define 	KEY_LASER_MODE2_EXTI_IRQn EXTI10_15_IRQn

	//LASER_MODE3:PA7
#define 	KEY_LASER_MODE3_PORT	GPIOA
#define 	KEY_LASER_MODE3_PIN 	GPIO_PIN_7
#define 	KEY_LASER_MODE3_CLK 	RCU_GPIOA
#define 	KEY_LASER_MODE3_EXTI_LINE EXTI_7
#define 	KEY_LASER_MODE3_EXTI_PORT_SOURCE GPIO_PORT_SOURCE_GPIOA
#define 	KEY_LASER_MODE3_EXTI_PIN_SOURCE GPIO_PIN_SOURCE_7
#define 	KEY_LASER_MODE3_EXTI_IRQn EXTI5_9_IRQn

	//LASER_MODE4:PA0
#define 	KEY_LASER_MODE4_PORT	GPIOA
#define 	KEY_LASER_MODE4_PIN 	GPIO_PIN_0
#define 	KEY_LASER_MODE4_CLK 	RCU_GPIOA
#define 	KEY_LASER_MODE4_EXTI_LINE EXTI_0
#define 	KEY_LASER_MODE4_EXTI_PORT_SOURCE GPIO_PORT_SOURCE_GPIOA
#define 	KEY_LASER_MODE4_EXTI_PIN_SOURCE GPIO_PIN_SOURCE_0
#define 	KEY_LASER_MODE4_EXTI_IRQn EXTI0_IRQn

	//Manual focal length adjust buttons.
	//KEY_FL_ADD:PA8
#define 	KEY_FL_ADD_PORT 		GPIOA
#define 	KEY_FL_ADD_PIN			GPIO_PIN_8
#define 	KEY_FL_ADD_CLK			RCU_GPIOA
#define 	KEY_FL_ADD_EXTI_LINE	EXTI_8
#define 	KEY_FL_ADD_EXTI_PORT_SOURCE GPIO_PORT_SOURCE_GPIOA
#define 	KEY_FL_ADD_EXTI_PIN_SOURCE GPIO_PIN_SOURCE_8
#define 	KEY_FL_ADD_EXTI_IRQn	EXTI5_9_IRQn

	//KEY_FL_SUB:PA11
#define 	KEY_FL_SUB_PORT 		GPIOA
#define 	KEY_FL_SUB_PIN			GPIO_PIN_11
#define 	KEY_FL_SUB_CLK			RCU_GPIOA
#define 	KEY_FL_SUB_EXTI_LINE	EXTI_11
#define 	KEY_FL_SUB_EXTI_PORT_SOURCE GPIO_PORT_SOURCE_GPIOA
#define 	KEY_FL_SUB_EXTI_PIN_SOURCE GPIO_PIN_SOURCE_11
#define 	KEY_FL_SUB_EXTI_IRQn	EXTI10_15_IRQn

	//Laser shot trigger switch.
	//KEY_SHOT_SW1:PC9
#define 	KEY_SHOT_SW1_PORT		GPIOC
#define 	KEY_SHOT_SW1_PIN		GPIO_PIN_9
#define 	KEY_SHOT_SW1_CLK		RCU_GPIOC
#define 	KEY_SHOT_SW1_EXTI_LINE	EXTI_9
#define 	KEY_SHOT_SW1_EXTI_PORT_SOURCE GPIO_PORT_SOURCE_GPIOC
#define 	KEY_SHOT_SW1_EXTI_PIN_SOURCE GPIO_PIN_SOURCE_9
#define 	KEY_SHOT_SW1_EXTI_IRQn	EXTI5_9_IRQn

	//KEY_SHOT_SW2:PC8 
#define 	KEY_SHOT_SW2_PORT		GPIOC
#define 	KEY_SHOT_SW2_PIN		GPIO_PIN_8
#define 	KEY_SHOT_SW2_CLK		RCU_GPIOC
#define 	KEY_SHOT_SW2_EXTI_LINE	EXTI_8
#define 	KEY_SHOT_SW2_EXTI_PORT_SOURCE GPIO_PORT_SOURCE_GPIOC
#define 	KEY_SHOT_SW2_EXTI_PIN_SOURCE GPIO_PIN_SOURCE_8
#define 	KEY_SHOT_SW2_EXTI_IRQn	EXTI5_9_IRQn

//COM0,COM1,COM2,COM3,COM4.
#define 	COMn					5U
#define 	COM0					USART0
#define 	COM0_CLK				RCU_USART0
#define 	COM0_TX_PIN 			GPIO_PIN_9
#define 	COM0_RX_PIN 			GPIO_PIN_10
#define 	COM0_GPIO_PORT			GPIOA
#define 	COM0_GPIO_CLK			RCU_GPIOA

#define 	COM1					USART1
#define 	COM1_CLK				RCU_USART1
#define 	COM1_TX_PIN 			GPIO_PIN_2
#define 	COM1_RX_PIN 			GPIO_PIN_3
#define 	COM1_GPIO_PORT			GPIOA
#define 	COM1_GPIO_CLK			RCU_GPIOA

#define 	COM2					USART2
#define 	COM2_CLK				RCU_USART2
#define 	COM2_TX_PIN 			GPIO_PIN_10
#define 	COM2_RX_PIN 			GPIO_PIN_11
#define 	COM2_GPIO_PORT			GPIOB
#define 	COM2_GPIO_CLK			RCU_GPIOB

#define 	COM3					UART3
#define 	COM3_CLK				RCU_UART3
#define 	COM3_TX_PIN 			GPIO_PIN_10
#define 	COM3_RX_PIN 			GPIO_PIN_11
#define 	COM3_GPIO_PORT			GPIOC
#define 	COM3_GPIO_CLK			RCU_GPIOC

#define 	COM4					UART4
#define 	COM4_CLK				RCU_UART4
#define 	COM4_TX_PIN 			GPIO_PIN_12
#define 	COM4_RX_PIN 			GPIO_PIN_12
#define 	COM4_GPIO_PORT1 		GPIOC
#define 	COM4_GPIO_PORT2 		GPIOD
#define 	COM4_GPIO_CLK1			RCU_GPIOC
#define 	COM4_GPIO_CLK2			RCU_GPIOD


	/* configure led GPIO */
	void z_led_init(zled_typedef_enum lednum);

	/* turn on selected led */
	void z_led_on(zled_typedef_enum lednum);

	/* turn off selected led */
	void z_led_off(zled_typedef_enum lednum);

	/* toggle the selected led */
	void z_led_toggle(zled_typedef_enum lednum);

	typedef enum {
		KEY_MODE_GPIO = 0, 
		KEY_MODE_EXTI = 1
	} zkeymode_typedef_enum;


	/* configure key */
	void z_key_init(zkey_typedef_enum key_num, zkeymode_typedef_enum key_mode);

	/* return the selected key state */
	uint8_t z_key_state_get(zkey_typedef_enum key);

	/* configure COM port */
	void z_com_init(uint32_t com);

	//to compatible with c++ compiler.
#ifdef __cplusplus
}


#endif

#endif //_ZSY_GD32F303RGT6_H__

