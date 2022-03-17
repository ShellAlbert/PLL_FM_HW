

/*!
	\file	 gd32f30x_it.c
	\brief	 interrupt service routines

	\version 2017-02-10, V1.0.0, firmware for GD32F30x
	\version 2018-10-10, V1.1.0, firmware for GD32F30x
	\version 2018-12-25, V2.0.0, firmware for GD32F30x
	\version 2020-09-30, V2.1.0, firmware for GD32F30x
*/

/*
	Copyright (c) 2020, GigaDevice Semiconductor Inc.

	Redistribution and use in source and binary forms, with or without modification, 
are permitted provided that the following conditions are met:

	1. Redistributions of source code must retain the above copyright notice, this 
	   list of conditions and the following disclaimer.
	2. Redistributions in binary form must reproduce the above copyright notice, 
	   this list of conditions and the following disclaimer in the documentation 
	   and/or other materials provided with the distribution.
	3. Neither the name of the copyright holder nor the names of its contributors 
	   may be used to endorse or promote products derived from this software without 
	   specific prior written permission.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
OF SUCH DAMAGE.
*/
#include "gd32f30x_it.h"
#include "systick.h"
#include "board_gd32f303rgt6.h"

/*!
	\brief		this function handles NMI exception
	\param[in]	none
	\param[out] none
	\retval 	none
*/
void NMI_Handler(void)
{
}


/*!
	\brief		this function handles HardFault exception
	\param[in]	none
	\param[out] none
	\retval 	none
*/
void HardFault_Handler(void)
{
	/* if Hard Fault exception occurs, go to infinite loop */
	while (1) {
	}
}


/*!
	\brief		this function handles MemManage exception
	\param[in]	none
	\param[out] none
	\retval 	none
*/
void MemManage_Handler(void)
{
	/* if Memory Manage exception occurs, go to infinite loop */
	while (1) {
	}
}


/*!
	\brief		this function handles BusFault exception
	\param[in]	none
	\param[out] none
	\retval 	none
*/
void BusFault_Handler(void)
{
	/* if Bus Fault exception occurs, go to infinite loop */
	while (1) {
	}
}


/*!
	\brief		this function handles UsageFault exception
	\param[in]	none
	\param[out] none
	\retval 	none
*/
void UsageFault_Handler(void)
{
	/* if Usage Fault exception occurs, go to infinite loop */
	while (1) {
	}
}


/*!
	\brief		this function handles SVC exception
	\param[in]	none
	\param[out] none
	\retval 	none
*/
void SVC_Handler(void)
{
}


/*!
	\brief		this function handles DebugMon exception
	\param[in]	none
	\param[out] none
	\retval 	none
*/
void DebugMon_Handler(void)
{
}


/*!
	\brief		this function handles PendSV exception
	\param[in]	none
	\param[out] none
	\retval 	none
*/
void PendSV_Handler(void)
{
}


/*!
	\brief		this function handles SysTick exception
	\param[in]	none
	\param[out] none
	\retval 	none
*/
void SysTick_Handler(void)
{
	//SysTick is an independent Clock from AHB Prescaler.
	//It is different from other TIMERx.
	delay_decrement();
}


/*!
	\brief		this function handles TIMER1 interrupt request.
	\param[in]	none
	\param[out] none
	\retval 	none
*/
void TIMER1_IRQHandler(void)
{

}


/*!
	\brief		this function handles TIMER2 interrupt request.
	\param[in]	none
	\param[out] none
	\retval 	none
*/
void TIMER2_IRQHandler(void)
{
	if (SET == timer_interrupt_flag_get(TIMER2, TIMER_INT_FLAG_UP)) {
		/* clear channel 0 interrupt bit */
		timer_interrupt_flag_clear(TIMER2, TIMER_INT_FLAG_UP);

		iGblFlag			= !iGblFlag;

		if (iGblFlag) {
			gpio_bit_set(GPIOB, GPIO_PIN_3);
		}
		else {
			gpio_bit_reset(GPIOB, GPIO_PIN_3);
		}
	}
}


/*!
	\brief		this function handles TIMER3 interrupt request.
	\param[in]	none
	\param[out] none
	\retval 	none
*/
void TIMER3_IRQHandler(void)
{

}


void EXTI0_IRQHandler(void)
{
	if (RESET != exti_interrupt_flag_get(EXTI_0)) {
		//LEFT_SW:PB0
		if (RESET != gpio_input_bit_get(KEY_LEFT_PORT, KEY_LEFT_PIN)) {
			//set flag to indicate key was pressed.
			gBrdFlashLight.iKey[KEY_LEFT] = 1;
		}

		//LASER_MODE4:PA0
		if (RESET != gpio_input_bit_get(KEY_LASER_MODE4_PORT, KEY_LASER_MODE4_PIN)) {
			//set flag to indicate key was pressed.
			gBrdFlashLight.iKey[KEY_LASER_MODE4] = 1;
		}

		exti_interrupt_flag_clear(EXTI_0);
	}
}


void EXTI1_IRQHandler(void)
{

	if (RESET != exti_interrupt_flag_get(EXTI_1)) {
		//Day/Night mode switch key:PA1
		if (RESET != gpio_input_bit_get(KEY_DAY_NIGHT_PORT, KEY_DAY_NIGHT_PIN)) {
			//set flag to indicate key was pressed.
			gBrdFlashLight.iKey[KEY_DAY_NIGHT] = 1;
		}

		//RIGHT_SW:PB1
		if (RESET != gpio_input_bit_get(KEY_RIGHT_PORT, KEY_RIGHT_PIN)) {
			//set flag to indicate key was pressed.
			gBrdFlashLight.iKey[KEY_RIGHT] = 1;
		}

		exti_interrupt_flag_clear(EXTI_1);
	}

}


void EXTI2_IRQHandler(void)
{

}


void EXTI3_IRQHandler(void)
{

}


void EXTI4_IRQHandler(void)
{

	if (RESET != exti_interrupt_flag_get(EXTI_4)) {
		//Continous ON mode/Flash mode switch key:PB4
		if (RESET != gpio_input_bit_get(KEY_CON_FLASH_PORT, KEY_CON_FLASH_PIN)) {
			//set flag to indicate key was pressed.
			gBrdFlashLight.iKey[KEY_CON_FLASH] = 1;
		}

		//UP_SW:PC4
		if (RESET != gpio_input_bit_get(KEY_UP_PORT, KEY_UP_PIN)) {
			//set flag to indicate key was pressed.
			gBrdFlashLight.iKey[KEY_UP] = 1;
		}

		exti_interrupt_flag_clear(EXTI_4);
	}
}


void EXTI5_9_IRQHandler(void)
{

	if (RESET != exti_interrupt_flag_get(EXTI_5)) {
		//SET_SW:PB5
		if (RESET != gpio_input_bit_get(KEY_SET_PORT, KEY_SET_PIN)) {
			//set flag to indicate key was pressed.
			gBrdFlashLight.iKey[KEY_SET] = 1;
		}

		exti_interrupt_flag_clear(EXTI_5);
	}


	if (RESET != exti_interrupt_flag_get(EXTI_6)) {
		//LASER_MODE1:PA6
		if (RESET != gpio_input_bit_get(KEY_LASER_MODE1_PORT, KEY_LASER_MODE1_PIN)) {
			//set flag to indicate key was pressed.
			gBrdFlashLight.iKey[KEY_LASER_MODE1] = 1;
		}

		exti_interrupt_flag_clear(EXTI_6);
	}


	if (RESET != exti_interrupt_flag_get(EXTI_7)) {
		//LASER_MODE3:PA7
		if (RESET != gpio_input_bit_get(KEY_LASER_MODE3_PORT, KEY_LASER_MODE3_PIN)) {
			//set flag to indicate key was pressed.
			gBrdFlashLight.iKey[KEY_LASER_MODE3] = 1;
		}

		exti_interrupt_flag_clear(EXTI_7);
	}
}


/*!
	\brief		this function handles external lines 10 to 15 interrupt request
	\param[in]	none
	\param[out] none
	\retval 	none
*/
void EXTI10_15_IRQHandler(void)
{
	if (RESET != exti_interrupt_flag_get(EXTI_13)) {
		//LASER_MODE2:PC13
		if (RESET != gpio_input_bit_get(KEY_LASER_MODE2_PORT, KEY_LASER_MODE2_PIN)) {
			//set flag to indicate key was pressed.
			gBrdFlashLight.iKey[KEY_LASER_MODE2] = 1;
		}

		exti_interrupt_flag_clear(EXTI_13);
	}
}


/*!
	\brief		this function handles USART RBNE interrupt request and TBE interrupt request
	\param[in]	none
	\param[out] none
	\retval 	none
*/
void USART0_IRQHandler(void)
{
	if (RESET != usart_interrupt_flag_get(USART0, USART_INT_FLAG_RBNE)) {
		/* receive one data */
		gBrdFlashLight.sUsart0.rxbuffer[gBrdFlashLight.sUsart0.rxcount++] = usart_data_receive(USART0);

		//after received all expected data disable Receive IRQ.
		if (gBrdFlashLight.sUsart0.rxcount == gBrdFlashLight.sUsart0.rx_size) {
			usart_interrupt_disable(USART0, USART_INT_RBNE);
		}
	}

	if (RESET != usart_interrupt_flag_get(USART0, USART_INT_FLAG_TBE)) {
		/* transmit one data */
		usart_data_transmit(USART0, gBrdFlashLight.sUsart0.txbuffer[gBrdFlashLight.sUsart0.txcount++]);

		//after transmit all expected data disable Transmit IRQ.
		if (gBrdFlashLight.sUsart0.txcount == gBrdFlashLight.sUsart0.tx_size) {
			usart_interrupt_disable(USART0, USART_INT_TBE);
		}
	}
}


void USART1_IRQHandler(void)
{
	if (RESET != usart_interrupt_flag_get(USART1, USART_INT_FLAG_RBNE)) {
		/* receive one data */
		gBrdFlashLight.sUsart1.rxbuffer[gBrdFlashLight.sUsart1.rxcount++] = usart_data_receive(USART1);

		//after received all expected data disable Receive IRQ.
		if (gBrdFlashLight.sUsart1.rxcount == gBrdFlashLight.sUsart1.rx_size) {
			usart_interrupt_disable(USART1, USART_INT_RBNE);
		}
	}

	if (RESET != usart_interrupt_flag_get(USART1, USART_INT_FLAG_TBE)) {
		/* transmit one data */
		usart_data_transmit(USART1, gBrdFlashLight.sUsart1.txbuffer[gBrdFlashLight.sUsart1.txcount++]);

		//after transmit all expected data disable Transmit IRQ.
		if (gBrdFlashLight.sUsart1.txcount == gBrdFlashLight.sUsart1.tx_size) {
			usart_interrupt_disable(USART1, USART_INT_TBE);
		}
	}
}


void USART2_IRQHandler(void)
{

}


void UART3_IRQHandler(void)
{
}


void UART4_IRQHandler(void)
{
}


