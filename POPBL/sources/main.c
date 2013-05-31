/*********************************************************************
** 																	**
** project : POPBL			 										**
** filename : main.c 												**
** version : 1 														**
** date : January 16, 2013 											**
** 																	**
**********************************************************************
** 																	**
** Copyright (c) 2003, 					 							**
** All rights reserved. 											**
** 																	**
**********************************************************************
**																	**
**VERSION HISTORY:													**
**----------------													**
**Version : 1														**
**Date : January 16, 2013											**
**Revised by :														**
**Description : Original version. 									**
*********************************************************************/

#define _MAIN_C_SRC

/*********************************************************************
**																	**
** MODULES USED 													**
** 																	**
**********************************************************************/
/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"

/* Stellaris library includes. */
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "consolaLCD/console.h"
#include "pwm_generico.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "hw_ints.h"
#include "adc.h"
#include "gpio.h"

#include "clock.h"
#include "pines.h"
#include "display.h"
#include "system_tick.h"
/*********************************************************************
** 																	**
** GLOBAL VARIABLES 												**
** 																	**
**********************************************************************/
xTaskHandle xHandle_Task_Recibir_Infrarrojos; /*"Handle" de la tarea de
recibir infrarrojos*/
float sens1=0.0, sens2=0.0, sens3=0.0, sens4=0.0, sens5=0.0, sens6=0.0;
/*********************************************************************
** 																	**
** EXPORTED FUNCTIONS 												**
** 																	**
**********************************************************************/
/* The task functions. */
void vTask_Recibir_Infrarrojos( void *pvParameters );
void vTask_Idle( void *pvParameters );
void vTask_Control( void *pvParameters );
void vTask_Seguridad( void *pvParameters );
/*********************************************************************
** 																	**
** LOCAL FUNCTIONS 													**
void pwm_init(void);
** 																	**
**********************************************************************/
//void vTask_Seguridad( void *pvParameters );
void vTask_Display( void *pvParameters );
int main( void )
{
	/*
	 * Se inicializan el clock, el display, el teclado y los pines.
	 */
	CLOCK_inicializar_clock();
	//DISPLAY_inicializar();

	pwm_init();
	stellaris_1_initialize(); //Stellaris


	KEYPAD_inicializacion_keypad();
//	PINES_inicializar(PORT_B,0);
//	PINES_inicializar(PORT_B,1);

	//PINES_inicializar(PORT_B,4);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	PINES_inicializar(PORT_D,6);
	PINES_inicializar(PORT_D,7);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_0);
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 0);
	/*Inicializar los pines de control del MUX*/
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
	GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_5); /*A*/
	GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_7); /*B*/
	GPIOPadConfigSet(GPIO_PORTC_BASE, GPIO_PIN_5|GPIO_PIN_7,GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPD);
	GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_5, 0);
	GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7, 0);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOG);
	GPIOPinTypeGPIOOutput(GPIO_PORTG_BASE, GPIO_PIN_0);
	GPIOPinWrite(GPIO_PORTG_BASE, GPIO_PIN_0, 0); /*INH*/
	//Inicialización del ADC
	SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
	SysCtlADCSpeedSet (SYSCTL_ADCSPEED_125KSPS);// Configure the sample-rate
	GPIOPinTypeADC (GPIO_PORTE_BASE, GPIO_PIN_7);
	GPIOPinTypeADC (GPIO_PORTE_BASE, GPIO_PIN_6);
	ADCSequenceConfigure (ADC0_BASE, 3, ADC_TRIGGER_PROCESSOR, 0);
	ADCSequenceEnable (ADC0_BASE, 3);
	/*
	 * Se inicializan las interrupciones del puerto B
	 */
/*	PINES_inicializar_int_both_edges(PORT_B, 0);
	PINES_inicializar_int_both_edges(PORT_B, 1);*/
	PINES_inicializar_int_both_edges(PORT_D, 6);
	PINES_inicializar_int_both_edges(PORT_D, 7);
	/*
	 * Se crean las tareas
	 */
	xTaskCreate( vTask_Recibir_Infrarrojos,"vTask_Recibir_Infrarrojos",200, 10 ,4, &xHandle_Task_Recibir_Infrarrojos );
	xTaskCreate( vTask_Idle,"vTask_Idle",200, 1000 ,1, NULL );
	xTaskCreate( vTask_Control,"vTask_Control",200, 1000 , 2, NULL );
	//xTaskCreate( vTask_Seguridad,"vTask_Seguridad",200, 100 , 5, NULL );
	xTaskCreate( vTask_Seguridad,"vTask_Seguridad",200, 1000 , 5, NULL );
	xTaskCreate( vTask_Display,"vTask_Display",200, 1 , 3, NULL );
	/*
	 * Se suspende la tarea para recibir los infrarrojos
	 */
	vTaskSuspend(xHandle_Task_Recibir_Infrarrojos); 
	/*
	 * Comienza el planeador
	 */
  vTaskStartScheduler();
  for( ;; );
}
/*********************************************************************
** 																	**
** EOF 																**
** 																	**
**********************************************************************/







