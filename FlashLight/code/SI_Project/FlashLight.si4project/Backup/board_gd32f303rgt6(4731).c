

//board configuration file for FlashLight Project.
//Feburary 14,2022
//by Yantai Electrician
#include <gd32f30x.h>
#include "board_gd32f303rgt6.h"
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


static uint32_t COM_GPIO_PORT[COMn] =
{
	COM0_GPIO_PORT, COM1_GPIO_PORT, COM2_GPIO_PORT, COM3_GPIO_PORT, COM4_GPIO_PORT1, COM4_GPIO_PORT2
};


static rcu_periph_enum COM_GPIO_CLK[COMn] =
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
	WAKEUP_KEY_EXTI_LINE, 
	TAMPER_KEY_EXTI_LINE, 
	USER_KEY_EXTI_LINE
};


static uint8_t	KEY_PORT_SOURCE[KEYn] =
{
	WAKEUP_KEY_EXTI_PORT_SOURCE, 
	TAMPER_KEY_EXTI_PORT_SOURCE, 
	USER_KEY_EXTI_PORT_SOURCE
};


static uint8_t	KEY_PIN_SOURCE[KEYn] =
{
	WAKEUP_KEY_EXTI_PIN_SOURCE, 
	TAMPER_KEY_EXTI_PIN_SOURCE, 
	USER_KEY_EXTI_PIN_SOURCE
};


static uint8_t	KEY_IRQn[KEYn] =
{
	WAKEUP_KEY_EXTI_IRQn, 
	TAMPER_KEY_EXTI_IRQn, 
	USER_KEY_EXTI_IRQn
};


/* configure led GPIO */
void z_led_init(zled_typedef_enum lednum)
{
    /* enable the led clock */
    rcu_periph_clock_enable(GPIO_CLK[lednum]);
    /* configure led GPIO port */ 
    gpio_init(GPIO_PORT[lednum], GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ,GPIO_PIN[lednum]);

    GPIO_BC(GPIO_PORT[lednum]) = GPIO_PIN[lednum];

}


/* turn on selected led */
void z_led_on(zled_typedef_enum lednum)
{
	GPIO_BOP(GPIO_PORT[lednum]) = GPIO_PIN[lednum];
}


/* turn off selected led */
void z_led_off(zled_typedef_enum lednum)
{

}


/* toggle the selected led */
void z_led_toggle(zled_typedef_enum lednum)
{

}


/* configure key */
void z_key_init(zkey_typedef_enum key_num, zkeymode_typedef_enum key_mode)
{

}


/* return the selected key state */
uint8_t z_key_state_get(zkey_typedef_enum key)
{

}


/* configure COM port */
void z_com_init(uint32_t com)
{

}


