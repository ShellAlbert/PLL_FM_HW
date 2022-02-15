

//board configuration file for FlashLight Project.
//Feburary 14,2022
//by Yantai Electrician
#include <gd32f30x.h>
#include "board_gd32f303rgt6.h"
#include <stdio.h>

//LED.
static uint32_t GPIO_PORT[LEDn] =
{
	LED1_GPIO_PORT, LED2_GPIO_PORT
};


static uint32_t GPIO_PIN[LEDn] =
{
	LED1_PIN, LED2_PIN
};


static rcu_periph_enum GPIO_CLK[LEDn] =
{
	LED1_GPIO_CLK, LED2_GPIO_CLK
};


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


static uint32_t COM_GPIO_PORT[COMn+1] =
{
	COM0_GPIO_PORT, COM1_GPIO_PORT, COM2_GPIO_PORT, COM3_GPIO_PORT, COM4_GPIO_PORT1, COM4_GPIO_PORT2
};


static rcu_periph_enum COM_GPIO_CLK[COMn+1] =
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


/* configure led GPIO */
void zled_init(zled_typedef_enum lednum)
{
	/* enable the led clock */
	rcu_periph_clock_enable(GPIO_CLK[lednum]);

	/* configure led GPIO port */
	gpio_init(GPIO_PORT[lednum], GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN[lednum]);

	GPIO_BC(GPIO_PORT[lednum]) = GPIO_PIN[lednum];

}


/* turn on selected led */
void zled_on(zled_typedef_enum lednum)
{
	GPIO_BOP(GPIO_PORT[lednum]) = GPIO_PIN[lednum];
}


/* turn off selected led */
void zled_off(zled_typedef_enum lednum)
{
	GPIO_BC(GPIO_PORT[lednum]) = GPIO_PIN[lednum];
}


/* toggle the selected led */
void zled_toggle(zled_typedef_enum lednum)
{
	gpio_bit_write(GPIO_PORT[lednum], GPIO_PIN[lednum], 
		(bit_status) (1 - gpio_input_bit_get(GPIO_PORT[lednum], GPIO_PIN[lednum])));

}


/* configure key */
//KEY_MODE_GPIO: key will be used as simple IO
//KEY_MODE_EXTI: key will be connected to EXTI line with interrupt
void zkey_init(zkey_typedef_enum key_num, zkeymode_typedef_enum key_mode)
{
	/* enable the key clock */
	rcu_periph_clock_enable(KEY_CLK[key_num]);
	rcu_periph_clock_enable(RCU_AF);

	/* configure button pin as input */
	gpio_init(KEY_PORT[key_num], GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, KEY_PIN[key_num]);

	if (key_mode == KEY_MODE_EXTI) {
		/* enable and set key EXTI interrupt to the lowest priority */
		nvic_irq_enable(KEY_IRQn[key_num], 2U, 0U);

		/* connect key EXTI line to key GPIO pin */
		gpio_exti_source_select(KEY_PORT_SOURCE[key_num], KEY_PIN_SOURCE[key_num]);

		/* configure key EXTI line */
		exti_init(KEY_EXTI_LINE[key_num], EXTI_INTERRUPT, EXTI_TRIG_FALLING);
		exti_interrupt_flag_clear(KEY_EXTI_LINE[key_num]);
	}
}

uint8_t zkey_flags[KEYn]={0};

/* return the selected key state */
uint8_t zkey_state_get(zkey_typedef_enum key)
{
	return gpio_input_bit_get(KEY_PORT[key], KEY_PIN[key]);
}


/* configure COM port */
void zcom_init(uint32_t com)
{
    uint32_t com_id = 0U;
    if(COM0 == com){
        com_id = 0U;
    }else if(COM1 == com){
        com_id = 1U;
    }else if(COM2 == com){
        com_id = 2U;
    }else if(COM3 == com){
        com_id = 3U;
    }else if(COM4 == com){
        com_id = 4U;
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
int fputc(int ch, FILE *f)
{
    usart_data_transmit(USART0, (uint8_t)ch);
    while(RESET == usart_flag_get(USART0, USART_FLAG_TBE));
    return ch;
}
