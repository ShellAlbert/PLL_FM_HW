

//board configuration file for FlashLight Project.
//Feburary 14,2022
//by Yantai Electrician
#include <gd32f30x.h>
#include "board_gd32f303rgt6.h"
#include <stdio.h>

//global variable board-layer defination.
ZBoardStruct	gBrdFlashLight;

//keys.
static uint32_t KEY_PORT[KEYn] =
{
	KEY_DAY_NIGHT_PORT, KEY_CON_FLASH_PORT, 		///<
	KEY_UP_PORT, KEY_DOWN_PORT, KEY_LEFT_PORT, KEY_RIGHT_PORT, KEY_SET_PORT, ///<
	KEY_LASER_MODE1_PORT, KEY_LASER_MODE2_PORT, KEY_LASER_MODE3_PORT, KEY_LASER_MODE4_PORT, ///<
	KEY_FL_ADD_PORT, KEY_FL_SUB_PORT,				///<
	KEY_SHOT_SW1_PORT, KEY_SHOT_SW2_PORT
};


static uint32_t KEY_PIN[KEYn] =
{
	KEY_DAY_NIGHT_PIN, KEY_CON_FLASH_PIN,			///<
	KEY_UP_PIN, KEY_DOWN_PIN, KEY_LEFT_PIN, KEY_RIGHT_PIN, KEY_SET_PIN, ///<
	KEY_LASER_MODE1_PIN, KEY_LASER_MODE2_PIN, KEY_LASER_MODE3_PIN, KEY_LASER_MODE4_PIN, ///<
	KEY_FL_ADD_PIN, KEY_FL_SUB_PIN, 				///<
	KEY_SHOT_SW1_PIN, KEY_SHOT_SW2_PIN
};


static rcu_periph_enum KEY_CLK[KEYn] =
{
	KEY_DAY_NIGHT_CLK, KEY_CON_FLASH_CLK,			///<
	KEY_UP_CLK, KEY_DOWN_CLK, KEY_LEFT_CLK, KEY_RIGHT_CLK, KEY_SET_CLK, ///<
	KEY_LASER_MODE1_CLK, KEY_LASER_MODE2_CLK, KEY_LASER_MODE3_CLK, KEY_LASER_MODE4_CLK, ///<
	KEY_FL_ADD_CLK, KEY_FL_SUB_CLK, 				///<
	KEY_SHOT_SW1_CLK, KEY_SHOT_SW2_CLK
};


static exti_line_enum KEY_EXTI_LINE[KEYn] =
{
	KEY_DAY_NIGHT_EXTI_LINE, KEY_CON_FLASH_EXTI_LINE, ///<
	KEY_UP_EXTI_LINE, KEY_DOWN_EXTI_LINE, KEY_LEFT_EXTI_LINE, KEY_RIGHT_EXTI_LINE, KEY_SET_EXTI_LINE, ///<
	KEY_LASER_MODE1_EXTI_LINE, KEY_LASER_MODE2_EXTI_LINE, KEY_LASER_MODE3_EXTI_LINE, KEY_LASER_MODE4_EXTI_LINE, ///<
	KEY_FL_ADD_EXTI_LINE, KEY_FL_SUB_EXTI_LINE, 	///<
	KEY_SHOT_SW1_EXTI_LINE, KEY_SHOT_SW2_EXTI_LINE
};


static uint8_t	KEY_PORT_SOURCE[KEYn] =
{
	KEY_DAY_NIGHT_EXTI_PORT_SOURCE, KEY_CON_FLASH_EXTI_PORT_SOURCE, ///<
	KEY_UP_EXTI_PORT_SOURCE, KEY_DOWN_EXTI_PORT_SOURCE, KEY_LEFT_EXTI_PORT_SOURCE, KEY_RIGHT_EXTI_PORT_SOURCE, 
	KEY_SET_EXTI_PORT_SOURCE,						///<
	KEY_LASER_MODE1_EXTI_PORT_SOURCE, KEY_LASER_MODE2_EXTI_PORT_SOURCE, KEY_LASER_MODE3_EXTI_PORT_SOURCE, 
	KEY_LASER_MODE4_EXTI_PORT_SOURCE,				///<
	KEY_FL_ADD_EXTI_PORT_SOURCE, KEY_FL_SUB_EXTI_PORT_SOURCE, ///<
	KEY_SHOT_SW1_EXTI_PORT_SOURCE, KEY_SHOT_SW2_EXTI_PORT_SOURCE
};


static uint8_t	KEY_PIN_SOURCE[KEYn] =
{
	KEY_DAY_NIGHT_EXTI_PIN_SOURCE, KEY_CON_FLASH_EXTI_PIN_SOURCE, ///<
	KEY_UP_EXTI_PIN_SOURCE, KEY_DOWN_EXTI_PIN_SOURCE, KEY_LEFT_EXTI_PIN_SOURCE, KEY_RIGHT_EXTI_PIN_SOURCE, 
	KEY_SET_EXTI_PIN_SOURCE,						///<
	KEY_LASER_MODE1_EXTI_PIN_SOURCE, KEY_LASER_MODE2_EXTI_PIN_SOURCE, KEY_LASER_MODE3_EXTI_PIN_SOURCE, 
	KEY_LASER_MODE4_EXTI_PIN_SOURCE,				///<
	KEY_FL_ADD_EXTI_PIN_SOURCE, KEY_FL_SUB_EXTI_PIN_SOURCE, ///<
	KEY_SHOT_SW1_EXTI_PIN_SOURCE, KEY_SHOT_SW2_EXTI_PIN_SOURCE
};


static uint8_t	KEY_IRQn[KEYn] =
{
	KEY_DAY_NIGHT_EXTI_IRQn, KEY_CON_FLASH_EXTI_IRQn, ///<
	KEY_UP_EXTI_IRQn, KEY_DOWN_EXTI_IRQn, KEY_LEFT_EXTI_IRQn, KEY_RIGHT_EXTI_IRQn, KEY_SET_EXTI_IRQn, ///<
	KEY_LASER_MODE1_EXTI_IRQn, KEY_LASER_MODE2_EXTI_IRQn, KEY_LASER_MODE3_EXTI_IRQn, KEY_LASER_MODE4_EXTI_IRQn, ///<
	KEY_FL_ADD_EXTI_IRQn, KEY_FL_SUB_EXTI_IRQn, 	///<
	KEY_SHOT_SW1_EXTI_IRQn, KEY_SHOT_SW2_EXTI_IRQn
};


//LED1/2 to indicate system working status.
static void zled12_init(void)
{
	//LED1:PB3 
	//LED2:PA15
	//enable the led clock.
	rcu_periph_clock_enable(RCU_GPIOB);
	rcu_periph_clock_enable(RCU_GPIOA);

	//configure led GPIO port.
	gpio_init(GPIOB, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_3);
	gpio_init(GPIOA, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_15);

	//set bit to off LEDs.
	zled_on_off(1, 0);
	zled_on_off(2, 0);
}


//initial all Keys to EXTI mode.
static void zkeys_exti_init(void)
{
	uint8_t 		i;

	for (i = 0; i < KEY_MAX; i++) {
		/* enable the key clock */
		rcu_periph_clock_enable(KEY_CLK[i]);
		rcu_periph_clock_enable(RCU_AF);

		/* configure button pin as input */
		gpio_init(KEY_PORT[i], GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, KEY_PIN[i]);

		//key will be connected to EXTI line with interrupt.

		/* enable and set key EXTI interrupt to the lowest priority */
		nvic_irq_enable(KEY_IRQn[i], 2U, 0U);

		/* connect key EXTI line to key GPIO pin */
		gpio_exti_source_select(KEY_PORT_SOURCE[i], KEY_PIN_SOURCE[i]);

		/* configure key EXTI line */
		//Y=~A in schematic,so here is rising edge.
		exti_init(KEY_EXTI_LINE[i], EXTI_INTERRUPT, EXTI_TRIG_RISING);

		//exti_init(KEY_EXTI_LINE[i], EXTI_INTERRUPT, EXTI_TRIG_FALLING);
		exti_interrupt_flag_clear(KEY_EXTI_LINE[i]);
	}

}


//USART0: For Debug TTL-USB. (3.3V TTL Level)
static void zusart0_debug_init(void)
{
	//USART0_TX:PA9,USART0_RX:PA10

	/* USART0 interrupt configuration */
	nvic_irq_enable(USART0_IRQn, 0, 0);

	/* enable GPIO clock */
	rcu_periph_clock_enable(RCU_GPIOA);

	/* enable USART clock */
	rcu_periph_clock_enable(RCU_USART0);

	/* connect port to USARTx_Tx & USARTx_Rx*/
	gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_9);
	gpio_init(GPIOA, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_10);

	/* USART0 configure */
	usart_deinit(USART0);
	usart_baudrate_set(USART0, 115200U);
	usart_receive_config(USART0, USART_RECEIVE_ENABLE);
	usart_transmit_config(USART0, USART_TRANSMIT_ENABLE);
	usart_enable(USART0);
}


//USART1: To communicate with Laser Distance Module. (RS422,Full duplex)
static void zusart1_distance_init(void)
{
	//USART1_TX:PA2,USART1_RX:PA3

	/* enable GPIO clock */
	rcu_periph_clock_enable(RCU_GPIOA);

	/* enable USART clock */
	rcu_periph_clock_enable(RCU_USART1);

	/* connect port to USARTx_Tx & USARTx_Rx*/
	gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_2);
	gpio_init(GPIOA, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_3);

	/* USART1 configure */
	usart_deinit(USART1);
	usart_baudrate_set(USART1, 115200U);
	usart_receive_config(USART1, USART_RECEIVE_ENABLE);
	usart_transmit_config(USART1, USART_TRANSMIT_ENABLE);
	usart_enable(USART1);
}


//USART2: To communicate with Display module. (3.3V TTL Level)
static void zusart2_oled_init(void)
{
	//USART2_TX:PB10,USART2_RX:PB11

	/* enable GPIO clock */
	rcu_periph_clock_enable(RCU_GPIOB);

	/* enable USART clock */
	rcu_periph_clock_enable(RCU_USART2);

	/* connect port to USARTx_Tx & USARTx_Rx*/
	gpio_init(GPIOB, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_10);
	gpio_init(GPIOB, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_11);

	/* USART2 configure */
	usart_deinit(USART2);
	usart_baudrate_set(USART2, 115200U);
	usart_receive_config(USART2, USART_RECEIVE_ENABLE);
	usart_transmit_config(USART2, USART_TRANSMIT_ENABLE);
	usart_enable(USART2);
}


//UART3: To communicate with WiFi-UART module. (3.3V TTL Level)
static void zuart3_wifi_init(void)
{
	//UART3_TX:PC10,UART3_RX:PC11

	/* enable GPIO clock */
	rcu_periph_clock_enable(RCU_GPIOC);

	/* enable USART clock */
	rcu_periph_clock_enable(RCU_UART3);

	/* connect port to USARTx_Tx & USARTx_Rx*/
	gpio_init(GPIOC, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_10);
	gpio_init(GPIOC, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_11);

	/* UART3 configure */
	usart_deinit(UART3);
	usart_baudrate_set(UART3, 115200U);
	usart_receive_config(UART3, USART_RECEIVE_ENABLE);
	usart_transmit_config(UART3, USART_TRANSMIT_ENABLE);
	usart_enable(UART3);
}


//UART4: To communicate with Laser Module. (3.3V TTL Level)
static void zuart4_laser_init(void)
{
	//UART4_TX:PC12,UART4_RX:PD2

	/* enable GPIO clock */
	rcu_periph_clock_enable(RCU_GPIOC);
	rcu_periph_clock_enable(RCU_GPIOD);

	/* enable USART clock */
	rcu_periph_clock_enable(RCU_UART4);

	/* connect port to USARTx_Tx & USARTx_Rx*/
	gpio_init(GPIOC, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_12);
	gpio_init(GPIOD, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_2);

	/* UART4 configure */
	usart_deinit(UART4);
	usart_baudrate_set(UART4, 115200U);
	usart_receive_config(UART4, USART_RECEIVE_ENABLE);
	usart_transmit_config(UART4, USART_TRANSMIT_ENABLE);
	usart_enable(UART4);
}


//MCU SoC ADC0.
//use Timer1 to trigger ADC0 periodic conversation (DMA0-CH0).
//ADC012_IN13:PC0
//ADC012_IN12:PC1
//ADC012_IN11:PC2
//ADC012_IN10:PC3
static void zmcu_soc_adc0_init(void)
{
	timer_oc_parameter_struct timer_ocintpara;
	timer_parameter_struct timer_initpara;

	dma_parameter_struct dma_data_parameter;

	/* enable GPIOA clock */
	rcu_periph_clock_enable(RCU_GPIOA);

	/* enable ADC0 clock */
	rcu_periph_clock_enable(RCU_ADC0);

	/* enable DMA0 clock */
	rcu_periph_clock_enable(RCU_DMA0);

	/* enable timer1 clock */
	rcu_periph_clock_enable(RCU_TIMER1);

	/* config ADC clock */
	rcu_adc_clock_config(RCU_CKADC_CKAPB2_DIV4);

	/* config the GPIO as analog mode */
	//ADC012_IN13:PC0
	//ADC012_IN12:PC1
	//ADC012_IN11:PC2
	//ADC012_IN10:PC3
	gpio_init(GPIOC, GPIO_MODE_AIN, GPIO_OSPEED_MAX, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);

	//configure the TIMER peripheral

	/* TIMER1 configuration */
	timer_initpara.prescaler = 8399;
	timer_initpara.alignedmode = TIMER_COUNTER_EDGE;
	timer_initpara.counterdirection = TIMER_COUNTER_UP;
	timer_initpara.period = 9999;
	timer_initpara.clockdivision = TIMER_CKDIV_DIV1;
	timer_initpara.repetitioncounter = 0;
	timer_init(TIMER1, &timer_initpara);

	/* CH0 configuration in PWM mode1 */
	timer_ocintpara.ocpolarity = TIMER_OC_POLARITY_HIGH;
	timer_ocintpara.outputstate = TIMER_CCX_ENABLE;
	timer_channel_output_config(TIMER1, TIMER_CH_1, &timer_ocintpara);

	timer_channel_output_pulse_value_config(TIMER1, TIMER_CH_1, 3999);
	timer_channel_output_mode_config(TIMER1, TIMER_CH_1, TIMER_OC_MODE_PWM1);
	timer_channel_output_shadow_config(TIMER1, TIMER_CH_1, TIMER_OC_SHADOW_DISABLE);

	//configure the DMA peripheral

	/* ADC DMA_channel configuration */
	dma_deinit(DMA0, DMA_CH0);


	/* initialize DMA data mode */
	dma_data_parameter.periph_addr = (uint32_t) (&ADC_RDATA(ADC0));
	dma_data_parameter.periph_inc = DMA_PERIPH_INCREASE_DISABLE;
	dma_data_parameter.memory_addr = (uint32_t) (&gBrdFlashLight.iMCUADC);
	dma_data_parameter.memory_inc = DMA_MEMORY_INCREASE_ENABLE;
	dma_data_parameter.periph_width = DMA_PERIPHERAL_WIDTH_32BIT;
	dma_data_parameter.memory_width = DMA_MEMORY_WIDTH_32BIT;
	dma_data_parameter.direction = DMA_PERIPHERAL_TO_MEMORY;
	dma_data_parameter.number = 4;
	dma_data_parameter.priority = DMA_PRIORITY_HIGH;
	dma_init(DMA0, DMA_CH0, &dma_data_parameter);

	dma_circulation_enable(DMA0, DMA_CH0);

	/* enable DMA channel */
	dma_channel_enable(DMA0, DMA_CH0);

	//configure the ADC peripheral

	/* ADC continous function enable */
	adc_special_function_config(ADC0, ADC_SCAN_MODE, ENABLE);
	adc_special_function_config(ADC0, ADC_CONTINUOUS_MODE, DISABLE);

	/* ADC trigger config */
	adc_external_trigger_source_config(ADC0, ADC_REGULAR_CHANNEL, ADC0_1_EXTTRIG_REGULAR_T1_CH1);

	/* ADC data alignment config */
	adc_data_alignment_config(ADC0, ADC_DATAALIGN_RIGHT);

	/* ADC mode config */
	adc_mode_config(ADC_DAUL_REGULAL_PARALLEL);

	/* ADC channel length config */
	adc_channel_length_config(ADC0, ADC_REGULAR_CHANNEL, 4);

	/* ADC regular channel config */
	adc_regular_channel_config(ADC0, 10, ADC_CHANNEL_10, ADC_SAMPLETIME_55POINT5);
	adc_regular_channel_config(ADC0, 11, ADC_CHANNEL_11, ADC_SAMPLETIME_55POINT5);
	adc_regular_channel_config(ADC0, 12, ADC_CHANNEL_12, ADC_SAMPLETIME_55POINT5);
	adc_regular_channel_config(ADC0, 13, ADC_CHANNEL_13, ADC_SAMPLETIME_55POINT5);


	/* ADC external trigger enable */
	adc_external_trigger_config(ADC0, ADC_REGULAR_CHANNEL, ENABLE);

	/* enable ADC interface */
	adc_enable(ADC0);
	delay_1ms(1);

	/* ADC calibration and reset calibration */
	adc_calibration_enable(ADC0);

	/* ADC DMA function enable */
	adc_dma_mode_enable(ADC0);

	/* enable TIMER1 */
	timer_enable(TIMER1);

}


//Timer3 to output pwm to drive brush DC motor.
static void ztimer3_bdcm_init(void)
{
	timer_oc_parameter_struct timer_ocintpara;
	timer_parameter_struct timer_initpara;

	//Configure the GPIO ports.
	rcu_periph_clock_enable(RCU_GPIOB);
	rcu_periph_clock_enable(RCU_AF);

	//Configure PB6 PB7(TIMER3 CH0 CH1) as alternate function.
	gpio_init(GPIOB, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_6);
	gpio_init(GPIOB, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_7);

	//Configure the TIMER peripheral.

	/* -----------------------------------------------------------------------
	TIMER3 configuration: generate 2 PWM signals with 2 different duty cycles:
	TIMER3CLK = SystemCoreClock / 120 = 1MHz

	TIMER3 channel0 duty cycle = (4000/ 16000)* 100  = 25%
	TIMER3 channel1 duty cycle = (8000/ 16000)* 100  = 50%
	----------------------------------------------------------------------- */
	rcu_periph_clock_enable(RCU_TIMER3);

	timer_deinit(TIMER3);

	/* TIMER1 configuration */
	timer_initpara.prescaler = 119;
	timer_initpara.alignedmode = TIMER_COUNTER_EDGE;
	timer_initpara.counterdirection = TIMER_COUNTER_UP;
	timer_initpara.period = 15999;
	timer_initpara.clockdivision = TIMER_CKDIV_DIV1;
	timer_initpara.repetitioncounter = 0;
	timer_init(TIMER3, &timer_initpara);

	/* CH0 and CH1 configuration in PWM mode */
	timer_ocintpara.outputstate = TIMER_CCX_ENABLE;
	timer_ocintpara.outputnstate = TIMER_CCXN_DISABLE;
	timer_ocintpara.ocpolarity = TIMER_OC_POLARITY_HIGH;
	timer_ocintpara.ocnpolarity = TIMER_OCN_POLARITY_HIGH;
	timer_ocintpara.ocidlestate = TIMER_OC_IDLE_STATE_LOW;
	timer_ocintpara.ocnidlestate = TIMER_OCN_IDLE_STATE_LOW;

	timer_channel_output_config(TIMER3, TIMER_CH_0, &timer_ocintpara);
	timer_channel_output_config(TIMER3, TIMER_CH_1, &timer_ocintpara);

	/* CH0 configuration in PWM mode0,duty cycle 25% */
	timer_channel_output_pulse_value_config(TIMER3, TIMER_CH_0, 3999);
	timer_channel_output_mode_config(TIMER3, TIMER_CH_0, TIMER_OC_MODE_PWM0);
	timer_channel_output_shadow_config(TIMER3, TIMER_CH_0, TIMER_OC_SHADOW_DISABLE);

	/* CH1 configuration in PWM mode0,duty cycle 50% */
	timer_channel_output_pulse_value_config(TIMER3, TIMER_CH_1, 7999);
	timer_channel_output_mode_config(TIMER3, TIMER_CH_1, TIMER_OC_MODE_PWM0);
	timer_channel_output_shadow_config(TIMER3, TIMER_CH_1, TIMER_OC_SHADOW_DISABLE);

	/* auto-reload preload enable */
	timer_auto_reload_shadow_enable(TIMER3);

	/* auto-reload preload enable */
	timer_enable(TIMER3);
}


//Timer7 to output pwm to drive brush DC motor.
static void ztimer7_bdcm_init(void)
{
	timer_oc_parameter_struct timer_ocintpara;
	timer_parameter_struct timer_initpara;

	//Configure the GPIO ports.
	rcu_periph_clock_enable(RCU_GPIOC);
	rcu_periph_clock_enable(RCU_AF);

	//Configure PC6 PC7(TIMER7 CH0 CH1) as alternate function.
	gpio_init(GPIOC, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_6);
	gpio_init(GPIOC, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_7);

	//Configure the TIMER peripheral.

	/* -----------------------------------------------------------------------
	TIMER7 configuration: generate 2 PWM signals with 2 different duty cycles:
	TIMER7CLK = SystemCoreClock / 120 = 1MHz

	TIMER7 channel0 duty cycle = (4000/ 16000)* 100  = 25%
	TIMER7 channel1 duty cycle = (8000/ 16000)* 100  = 50%
	----------------------------------------------------------------------- */
	rcu_periph_clock_enable(RCU_TIMER7);

	timer_deinit(TIMER7);

	/* TIMER1 configuration */
	timer_initpara.prescaler = 119;
	timer_initpara.alignedmode = TIMER_COUNTER_EDGE;
	timer_initpara.counterdirection = TIMER_COUNTER_UP;
	timer_initpara.period = 15999;
	timer_initpara.clockdivision = TIMER_CKDIV_DIV1;
	timer_initpara.repetitioncounter = 0;
	timer_init(TIMER7, &timer_initpara);

	/* CH0 and CH1 configuration in PWM mode */
	timer_ocintpara.outputstate = TIMER_CCX_ENABLE;
	timer_ocintpara.outputnstate = TIMER_CCXN_DISABLE;
	timer_ocintpara.ocpolarity = TIMER_OC_POLARITY_HIGH;
	timer_ocintpara.ocnpolarity = TIMER_OCN_POLARITY_HIGH;
	timer_ocintpara.ocidlestate = TIMER_OC_IDLE_STATE_LOW;
	timer_ocintpara.ocnidlestate = TIMER_OCN_IDLE_STATE_LOW;

	timer_channel_output_config(TIMER7, TIMER_CH_0, &timer_ocintpara);
	timer_channel_output_config(TIMER7, TIMER_CH_1, &timer_ocintpara);

	/* CH0 configuration in PWM mode0,duty cycle 25% */
	timer_channel_output_pulse_value_config(TIMER7, TIMER_CH_0, 3999);
	timer_channel_output_mode_config(TIMER7, TIMER_CH_0, TIMER_OC_MODE_PWM0);
	timer_channel_output_shadow_config(TIMER7, TIMER_CH_0, TIMER_OC_SHADOW_DISABLE);

	/* CH1 configuration in PWM mode0,duty cycle 50% */
	timer_channel_output_pulse_value_config(TIMER7, TIMER_CH_1, 7999);
	timer_channel_output_mode_config(TIMER7, TIMER_CH_1, TIMER_OC_MODE_PWM0);
	timer_channel_output_shadow_config(TIMER7, TIMER_CH_1, TIMER_OC_SHADOW_DISABLE);

	/* auto-reload preload enable */
	timer_auto_reload_shadow_enable(TIMER7);

	/* auto-reload preload enable */
	timer_enable(TIMER7);
}


//integrates all low-level components initialization.
void zboard_low_init(void)
{
	zled12_init();
	
#if 0
	//configure the TIMER peripheral
	timer_oc_parameter_struct timer_ocintpara;
	timer_parameter_struct timer_initpara;

	//configure the DMA peripheral
	dma_parameter_struct dma_data_parameter;

	//first initial global variables.
	gBrdFlashLight.sUsart0.fsm = FSM_PREPARE;

	//LED1/2 to indicate system working status.
	zled12_init();

	//initial all Keys to EXTI mode.
	zkeys_exti_init();

	//USART0: For Debug TTL-USB. (3.3V TTL Level)
	zusart0_debug_init();

	//USART1: To communicate with Laser Distance Module. (RS422,Full duplex)
	zusart1_distance_init();

	//USART2: To communicate with Display module. (3.3V TTL Level)
	zusart2_oled_init();

	//UART3: To communicate with WiFi-UART module. (3.3V TTL Level)
	zuart3_wifi_init();

	//UART4: To communicate with Laser Module. (3.3V TTL Level)
	zuart4_laser_init();


	//MCU SoC ADC0.
	//use Timer1 to trigger ADC0 periodic conversation (DMA0-CH0).
	zmcu_soc_adc0_init();

	//Timer3 to output pwm to drive brush DC motor.
	ztimer3_bdcm_init();

	//Timer7 to output pwm to drive brush DC motor.
	ztimer7_bdcm_init();
#endif
}


void zled_on_off(uint8_t iLed, uint8_t iOn)
{
	switch (iLed)
	{
		case 1:
			(iOn == 1) ? (GPIO_BC(GPIOB) = GPIO_PIN_3): (GPIO_BOP(GPIOB) = GPIO_PIN_3);
			break;

		case 2:
			(iOn == 1) ? (GPIO_BC(GPIOA) = GPIO_PIN_15): (GPIO_BOP(GPIOA) = GPIO_PIN_15);
			break;

		default:
			break;
	}
}


void zled_toggle(uint8_t iLed)
{
	switch (iLed)
	{
		case 1:
			gpio_bit_write(GPIOB, GPIO_PIN_3, (bit_status) (1 - gpio_input_bit_get(GPIOB, GPIO_PIN_3)));
			break;

		case 2:
			gpio_bit_write(GPIOA, GPIO_PIN_15, (bit_status) (1 - gpio_input_bit_get(GPIOA, GPIO_PIN_15)));
			break;

		default:
			break;
	}

}


/* retarget the C library printf function to the USART */
int fputc(int ch, FILE * f)
{
	usart_data_transmit(USART0, (uint8_t) ch);

	while (RESET == usart_flag_get(USART0, USART_FLAG_TBE))
		;

	return ch;
}


