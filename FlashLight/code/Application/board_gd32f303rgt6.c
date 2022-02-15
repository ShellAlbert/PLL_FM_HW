

//board configuration file for FlashLight Project.
//Feburary 14,2022
//by Yantai Electrician
#include <gd32f30x.h>
#include "board_gd32f303rgt6.h"
#include <stdio.h>

//global variable board-layer defination.
ZBoardStruct	gBrdFlashLight;


//COM0,COM1,COM2,COM3,COM4.
static rcu_periph_enum COM_CLK[COMn] =
{
	COM0_CLK, COM1_CLK, COM2_CLK, COM3_CLK, COM4_CLK
};


static uint32_t COM_TX_PIN[COMn] =
{
	COM0_TX_PIN, COM1_TX_PIN, COM2_TX_PIN, COM3_TX_PIN, COM4_TX_PIN
};


static uint32_t COM_RX_PIN[COMn] =
{
	COM0_RX_PIN, COM1_RX_PIN, COM2_RX_PIN, COM3_RX_PIN, COM4_RX_PIN
};


static uint32_t COM_GPIO_PORT[COMn + 1] =
{
	COM0_GPIO_PORT, COM1_GPIO_PORT, COM2_GPIO_PORT, COM3_GPIO_PORT, COM4_GPIO_PORT1, COM4_GPIO_PORT2
};


static rcu_periph_enum COM_GPIO_CLK[COMn + 1] =
{
	COM0_GPIO_CLK, COM1_GPIO_CLK, COM2_GPIO_CLK, COM3_GPIO_CLK, COM4_GPIO_CLK1, COM4_GPIO_CLK2
};


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


void zboard_low_init(void)
{
	uint8_t 		i;

	//1.initial LEDs.
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

	//2.initial KEYs.
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

	//3.initial USARTx and UARTx.
	//3.1.USART0_TX:PA9,USART0_RX:PA10

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

	//3.2.USART1_TX:PA2,USART1_RX:PA3

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

	//3.3.USART2_TX:PB10,USART2_RX:PB11

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

	//3.4.UART3_TX:PC10,UART3_RX:PC11

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

	//3.5.UART4_TX:PC12,UART4_RX:PD12

	/* enable GPIO clock */
	rcu_periph_clock_enable(RCU_GPIOC);
	rcu_periph_clock_enable(RCU_GPIOD);

	/* enable USART clock */
	rcu_periph_clock_enable(RCU_UART4);

	/* connect port to USARTx_Tx & USARTx_Rx*/
	gpio_init(GPIOC, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_12);
	gpio_init(GPIOD, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_12);

	/* UART4 configure */
	usart_deinit(UART4);
	usart_baudrate_set(UART4, 115200U);
	usart_receive_config(UART4, USART_RECEIVE_ENABLE);
	usart_transmit_config(UART4, USART_TRANSMIT_ENABLE);
	usart_enable(UART4);
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


/* configure COM port */
void zcom_init(uint32_t com)
{
	uint32_t		com_id = 0U;

	if (COM0 == com) {
		com_id				= 0U;
	}
	else if (COM1 == com) {
		com_id				= 1U;
	}
	else if (COM2 == com) {
		com_id				= 2U;
	}
	else if (COM3 == com) {
		com_id				= 3U;
	}
	else if (COM4 == com) {
		com_id				= 4U;
	}

	/* enable GPIO clock */
	rcu_periph_clock_enable(COM_GPIO_CLK[com_id]);

	/* enable USART clock */
	rcu_periph_clock_enable(COM_CLK[com_id]);

	/* connect port to USARTx_Tx */
	gpio_init(COM_GPIO_PORT[com_id], GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, COM_TX_PIN[com_id]);

	/* connect port to USARTx_Rx */
	gpio_init(COM_GPIO_PORT[com_id], GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, COM_RX_PIN[com_id]);

	/* USART configure */
	usart_deinit(com);
	usart_baudrate_set(com, 115200U);
	usart_receive_config(com, USART_RECEIVE_ENABLE);
	usart_transmit_config(com, USART_TRANSMIT_ENABLE);
	usart_enable(com);

}


/* retarget the C library printf function to the USART */
int fputc(int ch, FILE * f)
{
	usart_data_transmit(USART0, (uint8_t) ch);

	while (RESET == usart_flag_get(USART0, USART_FLAG_TBE))
		;

	return ch;
}


