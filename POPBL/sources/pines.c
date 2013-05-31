/*********************************************************************
 ** 																**
 ** project : POPBL			 										**
 ** filename : pines.c												**
 ** version : 1 													**
 ** date : January 16, 2013 										**
 ** 																**
 **********************************************************************
 ** 																**
 ** Copyright (c) 2003, 					 						**
 ** All rights reserved. 											**
 ** 																**
 **********************************************************************
 **																	**
 **VERSION HISTORY:													**
 **----------------													**
 **Version : 1														**
 **Date : January 16, 2013											**
 **Revised by :														**
 **Description : Original version. 									**
 *********************************************************************/
#define _PINES_C_SRC
/*********************************************************************
 **																	**
 ** MODULES USED 													**
 ** 																**
 **********************************************************************/
#include "pines.h"
/*********************************************************************
 ** 																**
 ** DEFINITIONS AND MACROS 											**
 ** 																**
 **********************************************************************/
#define TRUE 1
/*********************************************************************
 ** 																**
 ** EXPORTED VARIABLES 												**
 ** 																**
 *********************************************************************/
/*Variables globales que indican las interrupciones de los botones y de los pines*/
extern tBoolean g_arriba;
extern tBoolean g_abajo;
extern tBoolean g_izquierda;
extern tBoolean g_derecha;
extern tBoolean g_select;
/*********************************************************************
 ** 																**
 ** LOCAL FUNCTIONS 												**
 ** 																**
 **********************************************************************/
/**
 * @brief  Función para inicializar el pin 0 y el pin 1 del puerto B.
 *
 * @return      -
 *
*/
void PINES_inicializar(int ulport,
		int ucPins) {
	unsigned long puerto, periferico;
	unsigned char pin;
	switch (ucPins) {
	case 0:
		pin = GPIO_PIN_0;
		break;
	case 1:
		pin = GPIO_PIN_1;
		break;
	case 2:
		pin = GPIO_PIN_2;
		break;
	case 3:
		pin = GPIO_PIN_3;
		break;
	case 4:
		pin = GPIO_PIN_4;
		break;
	case 5:
		pin = GPIO_PIN_5;
		break;
	case 6:
		pin = GPIO_PIN_6;
		break;
	case 7:
		pin = GPIO_PIN_7;
		break;
	}
	switch (ulport) {
	case PORT_A:
		periferico = SYSCTL_PERIPH_GPIOA;
		puerto = GPIO_PORTA_BASE;
		break;
	case PORT_B:
		periferico = SYSCTL_PERIPH_GPIOB;
		puerto = GPIO_PORTB_BASE;
		break;
	case PORT_C:
		periferico = SYSCTL_PERIPH_GPIOC;
		puerto = GPIO_PORTC_BASE;
		break;
	case PORT_D:
		periferico = SYSCTL_PERIPH_GPIOD;
		puerto = GPIO_PORTD_BASE;
		break;
	case PORT_E:
		periferico = SYSCTL_PERIPH_GPIOE;
		puerto = GPIO_PORTE_BASE;
		break;
	case PORT_F:
		periferico = SYSCTL_PERIPH_GPIOF;
		puerto = GPIO_PORTF_BASE;
		break;
	case PORT_G:
		periferico = SYSCTL_PERIPH_GPIOG;
		puerto = GPIO_PORTG_BASE;
		break;
	}
	SysCtlPeripheralEnable(periferico);
	GPIOPinTypeGPIOInput(puerto, pin);
	GPIOPadConfigSet(puerto, pin, GPIO_STRENGTH_2MA,
			GPIO_PIN_TYPE_STD_WPD);

}
/**
 * @brief  Función para inicializar la interrupción del pin 0 y el pin 1 del puerto B.
 *
 * @return      -
 *
*/
void PINES_inicializar_int_both_edges(int ulport,
		int ucPins) {
	unsigned long puerto, periferico;
	unsigned char pin;
	switch (ucPins) {
	case 0:
		pin = GPIO_PIN_0;
		break;
	case 1:
		pin = GPIO_PIN_1;
		break;
	case 2:
		pin = GPIO_PIN_2;
		break;
	case 3:
		pin = GPIO_PIN_3;
		break;
	case 4:
		pin = GPIO_PIN_4;
		break;
	case 5:
		pin = GPIO_PIN_5;
		break;
	case 6:
		pin = GPIO_PIN_6;
		break;
	case 7:
		pin = GPIO_PIN_7;
		break;
	}
	switch (ulport) {
	case PORT_A:
		periferico = INT_GPIOA;
		puerto = GPIO_PORTA_BASE;
		break;
	case PORT_B:
		periferico = INT_GPIOB;
		puerto = GPIO_PORTB_BASE;
		break;
	case PORT_C:
		periferico = INT_GPIOC;
		puerto = GPIO_PORTC_BASE;
		break;
	case PORT_D:
		periferico = INT_GPIOD;
		puerto = GPIO_PORTD_BASE;
		break;
	case PORT_E:
		periferico = INT_GPIOE;
		puerto = GPIO_PORTE_BASE;
		break;
	case PORT_F:
		periferico = INT_GPIOF;
		puerto = GPIO_PORTF_BASE;
		break;
	case PORT_G:
		periferico = INT_GPIOG;
		puerto = GPIO_PORTG_BASE;
		break;
	}
	IntEnable(periferico);
	GPIOIntTypeSet(puerto, pin, GPIO_BOTH_EDGES);
	GPIOPinIntEnable(puerto, pin);
}
/**
 * @brief  Rutina de interrupción de los pines del puerto B.
 *
 * @return      -
 *
 * Se mira qué pin ha provocado la interrupción y estado en el que se encuentra ese pin
 * para saber si ha habido un flanco positivo o un flanco negativo.
*/
void __attribute__((interrupt)) PortBInterruptHandler(void) {
	unsigned long ul_port;
	unsigned char uc_pin;
	/*
	 * Guardamos el valor de la interrupción
	 */
	long temp = GPIOPinIntStatus(GPIO_PORTB_BASE, TRUE);

	/*
	 * Miramos si la interrupción ha sido provocada por el pin 0
	 */
	if (temp & GPIO_PIN_0) {
		unsigned long estado_pin;
		ul_port = GPIO_PORTB_BASE;
		uc_pin = GPIO_PIN_0;
		estado_pin = GPIOPinRead(ul_port, uc_pin);
		estado_pin = estado_pin & 0x1f;
		/*
		 * Si el flanco ha sido positivo
		 */
		if (estado_pin == 1) {
			g_arriba = 1;
			if ((xTaskIsTaskSuspended(xHandle_Task_Recibir_Infrarrojos))
					== true) {
				vTaskResume(xHandle_Task_Recibir_Infrarrojos);
			}
		}
		/*
		 * Si el flanco ha sido negativo
		 */
		else {
			g_abajo = 1;
		}
	}
	/*
	 * Miramos si la interrupción ha sido provocada por el pin 1
	 */
	if (temp & GPIO_PIN_1) {
		unsigned long estado_pin;
		ul_port = GPIO_PORTB_BASE;
		uc_pin = GPIO_PIN_1;
		estado_pin = GPIOPinRead(ul_port, uc_pin);
		estado_pin = estado_pin & 0x1f;
		/*
		 * Si el flanco ha sido positivo
		 */
		if (estado_pin == 1) {
			g_arriba = 1;
			if ((xTaskIsTaskSuspended(xHandle_Task_Recibir_Infrarrojos))
					== true) {
				vTaskResume(xHandle_Task_Recibir_Infrarrojos);
			}
		}
		/*
		 * Si el flanco ha sido negativo
		 */
		else {
			g_abajo = 1;
		}

	}
	/*
	 * Limpiamos la interrupción
	 */
	GPIOPinIntClear(ul_port, uc_pin);
}


void __attribute__((interrupt)) PortDInterruptHandler(void) {
	unsigned long ul_port;
	unsigned char uc_pin;
	/*
	 * Guardamos el valor de la interrupción
	 */
	long temp = GPIOPinIntStatus(GPIO_PORTD_BASE, TRUE);

	/*
	 * Miramos si la interrupción ha sido provocada por el pin 0
	 */
	if (temp & GPIO_PIN_6) {
		unsigned long estado_pin;
		ul_port = GPIO_PORTD_BASE;
		uc_pin = GPIO_PIN_6;
		estado_pin = GPIOPinRead(ul_port, uc_pin);
		//estado_pin = estado_pin & 0x1F;
		/*
		 * Si el flanco ha sido positivo
		 */
		if (estado_pin == 64) {
			g_arriba = 1;
			if ((xTaskIsTaskSuspended(xHandle_Task_Recibir_Infrarrojos))
					== true) {
				vTaskResume(xHandle_Task_Recibir_Infrarrojos);
			}
		}
		/*
		 * Si el flanco ha sido negativo
		 */
		else {
			g_abajo = 1;
		}
	}
	/*
	 * Miramos si la interrupción ha sido provocada por el pin 1
	 */
	if (temp & GPIO_PIN_7) {
		unsigned long estado_pin;
		ul_port = GPIO_PORTD_BASE;
		uc_pin = GPIO_PIN_7;
		estado_pin = GPIOPinRead(ul_port, uc_pin);
		//estado_pin = estado_pin & 0x80;
		/*
		 * Si el flanco ha sido positivo
		 */
		if (estado_pin == 128) {
			g_arriba = 1;
			if ((xTaskIsTaskSuspended(xHandle_Task_Recibir_Infrarrojos))
					== true) {
				vTaskResume(xHandle_Task_Recibir_Infrarrojos);
			}
		}
		/*
		 * Si el flanco ha sido negativo
		 */
		else {
			g_abajo = 1;
		}

	}
	/*
	 * Limpiamos la interrupción
	 */
	GPIOPinIntClear(ul_port, uc_pin);
}
/*********************************************************************
 ** 																	**
 ** EOF 																**
 ** 																	**
 **********************************************************************/
