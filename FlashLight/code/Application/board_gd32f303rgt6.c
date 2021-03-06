

//board configuration file for FlashLight Project.
//Feburary 14,2022
//by Yantai Electrician
#include <gd32f30x.h>
#include "board_gd32f303rgt6.h"
#include <stdio.h>

//global variable board-layer defination.
ZBoardStruct	gBrdFlashLight;
int8_t			iGblFlag = 0;
int8_t			iGblKeyFlag = 0;

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
	//PA15 was assigned to JTDI according to the Datasheet.
		//So here we remap to disable JTAG and enable SWD.
		//must enable AFIO clock before operate it.
		rcu_periph_clock_enable(RCU_AF);
		gpio_pin_remap_config(GPIO_SWJ_SWDPENABLE_REMAP, ENABLE);
		

	//LED:PB3 
	//enable the led clock.
	rcu_periph_clock_enable(RCU_GPIOB);

	//configure led GPIO port.
	gpio_init(GPIOB, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_3);

	//set bit to off LEDs.
	gpio_bit_reset(GPIOB, GPIO_PIN_3);


#if 1
	//PB5:12V_PWR_ON
	gpio_init(GPIOB, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_5);
	gpio_bit_set(GPIOB, GPIO_PIN_5);
 
	//PA8:WIFI_PWR_ON
	rcu_periph_clock_enable(RCU_GPIOA);
	gpio_init(GPIOA, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_8);
	gpio_bit_set(GPIOA, GPIO_PIN_8);
	
	//PC13:OLED_PWR_ON
	rcu_periph_clock_enable(RCU_GPIOC);
	gpio_init(GPIOC, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_13);
	gpio_bit_set(GPIOC, GPIO_PIN_13);

	//PA12:LDM_PWR_ON
	gpio_init(GPIOA, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_12);
	gpio_bit_set(GPIOA, GPIO_PIN_12);
#else
	//PB5:12V_PWR_ON
	gpio_init(GPIOB, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_5);
	gpio_bit_reset(GPIOB, GPIO_PIN_5);

	//PA8:WIFI_PWR_ON
	rcu_periph_clock_enable(RCU_GPIOA);
	gpio_init(GPIOA, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_8);
	gpio_bit_reset(GPIOA, GPIO_PIN_8);
	
	//PC13:OLED_PWR_ON
	rcu_periph_clock_enable(RCU_GPIOC);
	gpio_init(GPIOC, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_13);
	gpio_bit_reset(GPIOC, GPIO_PIN_13);

	//PA12:LDM_PWR_ON
	gpio_init(GPIOA, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_12);
	gpio_bit_reset(GPIOA, GPIO_PIN_12);
#endif
	
}


//initial all Keys to EXTI mode.
//PA0:LASER_MODE4, PA1:Day_Night, PA6:LASER_MODE1, PA7:LASER_MODE3, PA8:FL_ADD, PA11:FL_SUB
//PB0:LEFT_SW, PB1:RIGHT_SW, PB4:CON_Flash, PB5:SET_SW
//PC4:UP_SW, PC5:DOWN_SW, PC8:SHOT_SW2, PC9:SHOT_SW1, PC13:LASER_MODE2
static void zkeys_exti_init(void)
{
	rcu_periph_clock_enable(RCU_AF);
	rcu_periph_clock_enable(RCU_GPIOA);
	rcu_periph_clock_enable(RCU_GPIOB);
	rcu_periph_clock_enable(RCU_GPIOC);
	gpio_init(GPIOA, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_0); //PA0:LASER_MODE4
	gpio_init(GPIOA, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_1); //PA1:Day_Night
	gpio_init(GPIOA, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_6); //PA6:LASER_MODE1
	gpio_init(GPIOA, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_7); //PA7:LASER_MODE3
	gpio_init(GPIOA, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_8); //PA8:FL_ADD
	gpio_init(GPIOA, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_11); //PA11:FL_SUB

	gpio_init(GPIOB, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_0); //PB0:LEFT_SW
	gpio_init(GPIOB, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_1); //PB1:RIGHT_SW
	gpio_init(GPIOB, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_4); //PB4:CON_Flash
	gpio_init(GPIOB, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_5); //PB5:SET_SW

	gpio_init(GPIOC, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_4); //PC4:UP_SW
	gpio_init(GPIOC, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_5); //PC5:DOWN_SW
	gpio_init(GPIOC, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_8); //PC8:SHOT_SW2
	gpio_init(GPIOC, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_9); //PC9:SHOT_SW1
	gpio_init(GPIOC, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_13); //PC13:LASER_MODE2

	//key will be connected to EXTI line with interrupt.

	/* connect key EXTI line to key GPIO pin */
	gpio_exti_source_select(GPIO_PORT_SOURCE_GPIOA, GPIO_PIN_SOURCE_0);
	gpio_exti_source_select(GPIO_PORT_SOURCE_GPIOA, GPIO_PIN_SOURCE_1);
	gpio_exti_source_select(GPIO_PORT_SOURCE_GPIOA, GPIO_PIN_SOURCE_6);
	gpio_exti_source_select(GPIO_PORT_SOURCE_GPIOA, GPIO_PIN_SOURCE_7);
	gpio_exti_source_select(GPIO_PORT_SOURCE_GPIOA, GPIO_PIN_SOURCE_8);
	gpio_exti_source_select(GPIO_PORT_SOURCE_GPIOA, GPIO_PIN_SOURCE_11);

	gpio_exti_source_select(GPIO_PORT_SOURCE_GPIOB, GPIO_PIN_SOURCE_0);
	gpio_exti_source_select(GPIO_PORT_SOURCE_GPIOB, GPIO_PIN_SOURCE_1);
	gpio_exti_source_select(GPIO_PORT_SOURCE_GPIOB, GPIO_PIN_SOURCE_4);
	gpio_exti_source_select(GPIO_PORT_SOURCE_GPIOB, GPIO_PIN_SOURCE_5);

	gpio_exti_source_select(GPIO_PORT_SOURCE_GPIOC, GPIO_PIN_SOURCE_4);
	gpio_exti_source_select(GPIO_PORT_SOURCE_GPIOC, GPIO_PIN_SOURCE_5);
	gpio_exti_source_select(GPIO_PORT_SOURCE_GPIOC, GPIO_PIN_SOURCE_8);
	gpio_exti_source_select(GPIO_PORT_SOURCE_GPIOC, GPIO_PIN_SOURCE_9);
	gpio_exti_source_select(GPIO_PORT_SOURCE_GPIOC, GPIO_PIN_SOURCE_13);

	nvic_priority_group_set(NVIC_PRIGROUP_PRE2_SUB2);

	/* enable and set key EXTI interrupt to the lowest priority */
	nvic_irq_enable(EXTI0_IRQn, 2U, 0U);
	nvic_irq_enable(EXTI1_IRQn, 2U, 0U);
	nvic_irq_enable(EXTI4_IRQn, 2U, 0U);
	nvic_irq_enable(EXTI5_9_IRQn, 2U, 0U);
	nvic_irq_enable(EXTI10_15_IRQn, 2U, 0U);


	/* configure key EXTI line */
	//Y=~A in schematic,so here is rising edge.
	exti_init(EXTI_0, EXTI_INTERRUPT, EXTI_TRIG_RISING);
	exti_init(EXTI_1, EXTI_INTERRUPT, EXTI_TRIG_RISING);
	exti_init(EXTI_4, EXTI_INTERRUPT, EXTI_TRIG_RISING);
	exti_init(EXTI_5, EXTI_INTERRUPT, EXTI_TRIG_RISING);
	exti_init(EXTI_6, EXTI_INTERRUPT, EXTI_TRIG_RISING);
	exti_init(EXTI_7, EXTI_INTERRUPT, EXTI_TRIG_RISING);
	exti_init(EXTI_8, EXTI_INTERRUPT, EXTI_TRIG_RISING);
	exti_init(EXTI_9, EXTI_INTERRUPT, EXTI_TRIG_RISING);
	exti_init(EXTI_11, EXTI_INTERRUPT, EXTI_TRIG_RISING);
	exti_init(EXTI_13, EXTI_INTERRUPT, EXTI_TRIG_RISING);

	exti_interrupt_flag_clear(EXTI_0);
	exti_interrupt_flag_clear(EXTI_1);
	exti_interrupt_flag_clear(EXTI_4);
	exti_interrupt_flag_clear(EXTI_5);
	exti_interrupt_flag_clear(EXTI_6);
	exti_interrupt_flag_clear(EXTI_7);
	exti_interrupt_flag_clear(EXTI_8);
	exti_interrupt_flag_clear(EXTI_9);
	exti_interrupt_flag_clear(EXTI_11);
	exti_interrupt_flag_clear(EXTI_13);


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
	rcu_periph_clock_enable(RCU_GPIOC);

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
	timer_initpara.prescaler = 48000 - 1;			//IRC 120M/48000=2500Hz.Prescale maximum is 65536.
	timer_initpara.alignedmode = TIMER_COUNTER_EDGE;
	timer_initpara.counterdirection = TIMER_COUNTER_UP;
	timer_initpara.period = 1250 - 1;				//2500/1250=2Hz
	timer_initpara.clockdivision = TIMER_CKDIV_DIV1;
	timer_initpara.repetitioncounter = 0;
	timer_init(TIMER1, &timer_initpara);

	/* CH0 configuration in PWM mode1 */
	timer_ocintpara.ocpolarity = TIMER_OC_POLARITY_HIGH;
	timer_ocintpara.outputstate = TIMER_CCX_ENABLE;
	timer_channel_output_config(TIMER1, TIMER_CH_1, &timer_ocintpara);

	//here we set 500(because previous we set period=1250-1)
	//so here is trigger periodly.
	timer_channel_output_pulse_value_config(TIMER1, TIMER_CH_1, 500);
	timer_channel_output_mode_config(TIMER1, TIMER_CH_1, TIMER_OC_MODE_PWM0);
	timer_channel_output_shadow_config(TIMER1, TIMER_CH_1, TIMER_OC_SHADOW_DISABLE);
	timer_auto_reload_shadow_enable(TIMER1);


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
	dma_data_parameter.number = 4 * 50; 			//4 channels,each channels samples 50 times.
	dma_data_parameter.priority = DMA_PRIORITY_HIGH;
	dma_init(DMA0, DMA_CH0, &dma_data_parameter);

	dma_circulation_enable(DMA0, DMA_CH0);
	nvic_irq_enable(DMA0_Channel0_IRQn, 0, 0);

	/* enable DMA transfer complete interrupt */
	dma_interrupt_enable(DMA0, DMA_CH0, DMA_INT_FTF);

	/* enable DMA channel */
	dma_channel_enable(DMA0, DMA_CH0);


	//configure the ADC peripheral

	/* ADC continous function enable */
	adc_special_function_config(ADC0, ADC_SCAN_MODE, ENABLE);
	adc_special_function_config(ADC0, ADC_CONTINUOUS_MODE, ENABLE);

	/* ADC trigger config */
	adc_external_trigger_source_config(ADC0, ADC_REGULAR_CHANNEL, ADC0_1_EXTTRIG_REGULAR_T1_CH1);

	/* ADC data alignment config */
	adc_data_alignment_config(ADC0, ADC_DATAALIGN_RIGHT);
	adc_resolution_config(ADC0, ADC_RESOLUTION_12B);

	/* ADC mode config */
	adc_mode_config(ADC_DAUL_REGULAL_PARALLEL);

	/* ADC channel length config */
	adc_channel_length_config(ADC0, ADC_REGULAR_CHANNEL, 4);

	/* ADC regular channel config */
	adc_regular_channel_config(ADC0, 0, ADC_CHANNEL_10, ADC_SAMPLETIME_55POINT5); //VDD12_MOTOR
	adc_regular_channel_config(ADC0, 1, ADC_CHANNEL_11, ADC_SAMPLETIME_55POINT5); //VSYS
	adc_regular_channel_config(ADC0, 2, ADC_CHANNEL_12, ADC_SAMPLETIME_55POINT5); //Motor1#Current
	adc_regular_channel_config(ADC0, 3, ADC_CHANNEL_13, ADC_SAMPLETIME_55POINT5); //Motor2#Current

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


//use Timer2 to schedule Tasks.
static void ztimer2_schedule_task_init(void)
{
	/* ---------------------------------------------------------------
		TIMER2 Configuration: 
		TIMER2CLK = SystemCoreClock / 1200 = 100KHz,
		1/100Hz=0.01s=10ms
		--------------------------------------------------------------- */
	timer_oc_parameter_struct timer_ocintpara;
	timer_parameter_struct timer_initpara;

	rcu_periph_clock_enable(RCU_TIMER2);

	timer_deinit(TIMER2);

	/* TIMER2 configuration */
	timer_initpara.prescaler = 1200 - 1;			//IRC 120M/1200=100KHz.Prescale maximum is 65536.
	timer_initpara.alignedmode = TIMER_COUNTER_EDGE;
	timer_initpara.counterdirection = TIMER_COUNTER_UP;
	timer_initpara.period = 1000 - 1;				//100KHz/1000=100Hz,1/100Hz=0.01s=10mS
	timer_initpara.clockdivision = TIMER_CKDIV_DIV1;
	timer_initpara.repetitioncounter = 0;
	timer_init(TIMER2, &timer_initpara);

	//close TIME2_CH0/CH1 to release PB4/PB5 pins.

	/* CH0 and CH1 configuration in PWM mode */
	timer_ocintpara.outputstate = TIMER_CCX_DISABLE;
	timer_ocintpara.outputnstate = TIMER_CCXN_DISABLE;
	timer_ocintpara.ocpolarity = TIMER_OC_POLARITY_LOW;
	timer_ocintpara.ocnpolarity = TIMER_OCN_POLARITY_LOW;
	timer_ocintpara.ocidlestate = TIMER_OC_IDLE_STATE_LOW;
	timer_ocintpara.ocnidlestate = TIMER_OCN_IDLE_STATE_LOW;

	timer_channel_output_config(TIMER2, TIMER_CH_0, &timer_ocintpara);
	timer_channel_output_config(TIMER2, TIMER_CH_1, &timer_ocintpara);


	/* auto-reload preload enable */
	timer_auto_reload_shadow_enable(TIMER2);
	timer_interrupt_flag_clear(TIMER2, TIMER_INT_FLAG_UP);

	/*interrupt enable */
	timer_interrupt_enable(TIMER2, TIMER_INT_UP);
	nvic_irq_enable(TIMER2_IRQn, 2U, 0U);
	timer_enable(TIMER2);

}


//Timer3 to output pwm to drive brush DC motor.
extern void ztimer3_bdcm_init(void)
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

	TIMER3 channel0 duty cycle = (5/ 10(period))* 100  = 50%
	TIMER3 channel1 duty cycle = (2/ 10(period))* 100  = 20%
	----------------------------------------------------------------------- */
	rcu_periph_clock_enable(RCU_TIMER3);

	timer_deinit(TIMER3);

	/* TIMER1 configuration */
	timer_initpara.prescaler = 120 - 1; 			//IRC 120M/120=1MHz.Prescale maximum is 65536.
	timer_initpara.alignedmode = TIMER_COUNTER_EDGE;
	timer_initpara.counterdirection = TIMER_COUNTER_UP;
	timer_initpara.period = 10 - 1; 				//1MHz/10=100kHz
	timer_initpara.clockdivision = TIMER_CKDIV_DIV1;
	timer_initpara.repetitioncounter = 0;
	timer_init(TIMER3, &timer_initpara);

	/* CH0 and CH1 configuration in PWM mode */
	timer_ocintpara.outputstate = TIMER_CCX_ENABLE;
	timer_ocintpara.outputnstate = TIMER_CCXN_DISABLE;
	timer_ocintpara.ocpolarity = TIMER_OC_POLARITY_LOW;
	timer_ocintpara.ocnpolarity = TIMER_OCN_POLARITY_LOW;
	timer_ocintpara.ocidlestate = TIMER_OC_IDLE_STATE_LOW;
	timer_ocintpara.ocnidlestate = TIMER_OCN_IDLE_STATE_LOW;

	timer_channel_output_config(TIMER3, TIMER_CH_0, &timer_ocintpara);
	timer_channel_output_config(TIMER3, TIMER_CH_1, &timer_ocintpara);

	/* CH0 configuration in PWM mode0,duty cycle 25% */
	//timer_channel_output_pulse_value_config(TIMER3, TIMER_CH_0, 40); //period/pwm=100/40=25%
	//set PWM to 0 to close channel output.
	timer_channel_output_pulse_value_config(TIMER3, TIMER_CH_0, 10); //period/pwm=100/100=0%


	timer_channel_output_mode_config(TIMER3, TIMER_CH_0, TIMER_OC_MODE_PWM0);
	timer_channel_output_shadow_config(TIMER3, TIMER_CH_0, TIMER_OC_SHADOW_DISABLE);

	/* CH1 configuration in PWM mode0,duty cycle 50% */
	timer_channel_output_pulse_value_config(TIMER3, TIMER_CH_1, 2); //period/pwm=100/50=50%

	//set PWM to 0 to close channel output.
	//timer_channel_output_pulse_value_config(TIMER3, TIMER_CH_1, 100);//period/pwm=100/100=0%
	timer_channel_output_mode_config(TIMER3, TIMER_CH_1, TIMER_OC_MODE_PWM0);
	timer_channel_output_shadow_config(TIMER3, TIMER_CH_1, TIMER_OC_SHADOW_DISABLE);

	/* auto-reload preload enable */
	timer_auto_reload_shadow_enable(TIMER3);

	/* auto-reload preload enable */
	timer_enable(TIMER3);
}


//Timer4 to flash LED.
static void ztimer4_led_init(void)
{
	timer_oc_parameter_struct timer_ocintpara;
	timer_parameter_struct timer_initpara;

	//Configure the TIMER peripheral.

	/* -----------------------------------------------------------------------
	TIMER4 configuration: generate 2 PWM signals with 2 different duty cycles:
	TIMER4CLK = SystemCoreClock / 120 = 1MHz

	TIMER4 channel0 duty cycle = (5/ 10(period))* 100  = 50%
	TIMER4 channel1 duty cycle = (2/ 10(period))* 100  = 20%
	----------------------------------------------------------------------- */
	rcu_periph_clock_enable(RCU_TIMER4);

	timer_deinit(TIMER4);

	/* TIMER1 configuration */
	timer_initpara.prescaler = 48000 - 1;			//IRC 120M/48000=2500Hz.Prescale maximum is 65536.
	timer_initpara.alignedmode = TIMER_COUNTER_EDGE;
	timer_initpara.counterdirection = TIMER_COUNTER_UP;
	timer_initpara.period = 1250 - 1;				//2500/1250=2Hz
	timer_initpara.clockdivision = TIMER_CKDIV_DIV1;
	timer_initpara.repetitioncounter = 0;
	timer_init(TIMER4, &timer_initpara);

	/* auto-reload preload enable */
	timer_auto_reload_shadow_enable(TIMER4);
	timer_interrupt_flag_clear(TIMER4, TIMER_INT_FLAG_UP);

	/*interrupt enable */
	timer_interrupt_enable(TIMER4, TIMER_INT_UP);
	nvic_irq_enable(TIMER4_IRQn, 2U, 0U);
	timer_enable(TIMER4);
}


//Timer7 to output pwm to drive brush DC motor.
extern void ztimer7_bdcm_init(void)
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
	timer_initpara.prescaler = 120 - 1; 			//IRC 120M/120=1MHz.Prescale maximum is 65536.
	timer_initpara.alignedmode = TIMER_COUNTER_EDGE;
	timer_initpara.counterdirection = TIMER_COUNTER_UP;
	timer_initpara.period = 10 - 1; 				//1MHz/10=100kHz
	timer_initpara.clockdivision = TIMER_CKDIV_DIV1;
	timer_initpara.repetitioncounter = 0;
	timer_init(TIMER7, &timer_initpara);

	/* CH0 and CH1 configuration in PWM mode */
	timer_ocintpara.outputstate = TIMER_CCX_ENABLE;
	timer_ocintpara.outputnstate = TIMER_CCXN_DISABLE;
	timer_ocintpara.ocpolarity = TIMER_OC_POLARITY_LOW;
	timer_ocintpara.ocnpolarity = TIMER_OCN_POLARITY_LOW;
	timer_ocintpara.ocidlestate = TIMER_OC_IDLE_STATE_LOW;
	timer_ocintpara.ocnidlestate = TIMER_OCN_IDLE_STATE_LOW;

	timer_channel_output_config(TIMER7, TIMER_CH_0, &timer_ocintpara);
	timer_channel_output_config(TIMER7, TIMER_CH_1, &timer_ocintpara);

	/* CH0 configuration in PWM mode0,duty cycle 25% */
	timer_channel_output_pulse_value_config(TIMER7, TIMER_CH_0, 2); //period/pwm=10/5=50%

	//set PWM to 0 to close channel output.
	//timer_channel_output_pulse_value_config(TIMER7, TIMER_CH_0, 10);//period/pwm=100/100=0%
	timer_channel_output_mode_config(TIMER7, TIMER_CH_0, TIMER_OC_MODE_PWM0);
	timer_channel_output_shadow_config(TIMER7, TIMER_CH_0, TIMER_OC_SHADOW_DISABLE);

	/* CH1 configuration in PWM mode0,duty cycle 50% */
	//timer_channel_output_pulse_value_config(TIMER7, TIMER_CH_1, 5);//period/pwm=10/5=50%
	//set PWM to 0 to close channel output.
	timer_channel_output_pulse_value_config(TIMER7, TIMER_CH_1, 10); //period/pwm=10/10=0%
	timer_channel_output_mode_config(TIMER7, TIMER_CH_1, TIMER_OC_MODE_PWM0);
	timer_channel_output_shadow_config(TIMER7, TIMER_CH_1, TIMER_OC_SHADOW_DISABLE);

	/* auto-reload preload enable */
	timer_auto_reload_shadow_enable(TIMER7);

	/*TIMER7 primary output function enable Only Advanced Timer0 and Timer7 needed.*/
	timer_primary_output_config(TIMER7, ENABLE);

	/* auto-reload preload enable */
	timer_enable(TIMER7);
}


//integrates all low-level components initialization.
void zboard_low_init(void)
{


	//configure the TIMER peripheral
	timer_oc_parameter_struct timer_ocintpara;
	timer_parameter_struct timer_initpara;

	//configure the DMA peripheral
	dma_parameter_struct dma_data_parameter;

	//first initial global variables.
	gBrdFlashLight.sUsart0.fsm = FSM_PREPARE;

	//LED1/2 to indicate system working status.
	zled12_init();
#if 0

	//initial all Keys to EXTI mode.
	zkeys_exti_init();

	//use Timer4 to driver LED in 1Hz.
	ztimer4_led_init();

	//Timer7 to output pwm to drive brush DC motor.
	//ztimer7_bdcm_init();
	//USART0: For Debug TTL-USB. (3.3V TTL Level)
	zusart0_debug_init();

	//USART1: To communicate with Laser Distance Module. (RS422,Full duplex)
	//zusart1_distance_init();
	//USART2: To communicate with Display module. (3.3V TTL Level)
	//zusart2_oled_init();
	//UART3: To communicate with WiFi-UART module. (3.3V TTL Level)
	//zuart3_wifi_init();
	//UART4: To communicate with Laser Module. (3.3V TTL Level)
	//zuart4_laser_init();
	//MCU SoC ADC0.
	//use Timer1 to trigger ADC0 periodic conversation (DMA0-CH0).
	zmcu_soc_adc0_init();

	//use Timer2 to generate 10mS to schedule all Tasks.
	ztimer2_schedule_task_init();

	//Timer3 to output pwm to drive brush DC motor.
	//ztimer3_bdcm_init();
#endif
}


void zled_on_off(uint8_t iLed, uint8_t iOn)
{
	switch (iLed)
	{
		case 1:
			(iOn == 1) ? (GPIO_BC(GPIOB) = GPIO_PIN_3): (GPIO_BOP(GPIOB) = GPIO_PIN_3);
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
		default:
			break;
	}

}


/* retarget the C library printf function to the USART */
int fputc(int ch, FILE * f)
{
#if 1
	usart_data_transmit(USART0, (uint8_t) ch);

	while (RESET == usart_flag_get(USART0, USART_FLAG_TBE))
		;

#endif
}


