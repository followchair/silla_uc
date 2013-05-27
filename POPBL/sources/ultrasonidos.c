/*********************************************************************
** 																	**
** project : POPBL													**
** filename : ultrasonidos.c										**
** version : 1 														**
** date : May 27, 2013												**
** 																	**
**********************************************************************
** 																	**
** Copyright (c) 2013, Irune, Ane, Aitor							**
** All rights reserved. 											**
** 																	**
**********************************************************************
**																	**
**VERSION HISTORY:													**
**----------------													**
**Version : 1														**
**Date : May 27, 2013												**
**Revised by : ---													**
**Description : Original version. 									**
*********************************************************************/
#define _ULTRASONIDOS_C_SRC
/*********************************************************************
**																	**
** MODULES USED 													**
** 																	**
**********************************************************************/
#include "ultrasonidos.h"
#include "consolaLCD/console.h"
#include "driverlib/systick.h"
/*********************************************************************
 ** 																**
 ** DEFINITIONS AND MACROS 											**
 ** 																**
 **********************************************************************/
#define TRUE 1
/*********************************************************************
** 																	**
** GLOBAL VARIABLES 												**
** 																	**
**********************************************************************/
/*Variables para guardar las interrupciones*/
tBoolean g_echo_arriba=0;
tBoolean g_echo_abajo=0;
tBoolean flancoPos = 0;
int time_flanco_pos=0;
int time_flanco_neg=0;
int echo_OK = 0;
/*********************************************************************
** 																	**
** LOCAL FUNCTIONS 													**
** 																	**
**********************************************************************/
/**
 * @brief  Se inicializan los modulos necesarios para los sensores de ultrasonidos
 *
 * @return      -
 *
 * PWM, pines etc.
 */
void ULTRASONIDOS_ini(void){

	unsigned long int ul_periodo_ultrasonid;
	/*
	 * Se inicializa el PWM para el pin de disparo de los sensores de ultrasonidos
	 */
	ul_periodo_ultrasonid = SysCtlClockGet ()/100; //80ms
	PWM_GENERICO_salida_init(PWM3, ul_periodo_ultrasonid );
	PWM_GENERICO_cambiar_anchura_pulso(0.00025 , PWM3, ul_periodo_ultrasonid); //pulso de 20uS

	/*
	 * Inicializar Pin ECHO: PD-4 -Input
	 */
	PINES_inicializar(PORT_D, 4);
	PINES_inicializar_int_both_edges(PORT_D, 4);
	//SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
	//GPIOPinTypeGPIOInput(GPIO_PORTB_BASE, GPIO_PIN_0);
	//GPIOPadConfigSet(GPIO_PORTB_BASE, GPIO_PIN_0,
	//				GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPD);


}

/**
 * @brief  Rutina de interrupción de los pines del puerto B.
 *
 * @return      -
 *
 * Se mira qué pin ha provocado la interrupción y estado en el que se encuentra ese pin
 * para saber si ha habido un flanco positivo o un flanco negativo.
*/
void __attribute__((interrupt))ULTRASONIDOS_echoInt_PD4(void) {
	unsigned long ul_port;
	unsigned char uc_pin;


	/*
	 * Guardamos el valor de la interrupción
	 */
	long temp = GPIOPinIntStatus(GPIO_PORTD_BASE, TRUE);
	/*
		 * Miramos si la interrupción ha sido provocada por el pin 0
		 */
		if (temp & GPIO_PIN_4) {
			unsigned long estado_pin;
			ul_port = GPIO_PORTD_BASE;
			uc_pin = GPIO_PIN_4;
			estado_pin = GPIOPinRead(ul_port, uc_pin);
			estado_pin = estado_pin & 0x1f;
			/*
			 * Si el flanco ha sido positivo
			 */
			if (estado_pin == 0x10) {
				time_flanco_pos = SysTickValueGet();
				flancoPos = 1;
			}
			/*
			 * Si el flanco ha sido negativo
			 */
			if (estado_pin == 0x00 && flancoPos == 1) {
				time_flanco_neg = SysTickValueGet();
				flancoPos = 0;
				echo_OK = 1;
			}
		}
		/*
		 * Limpiamos la interrupción
		 */
		GPIOPinIntClear(ul_port, uc_pin);
}

float ULTRASONIDOS_obstaculo(void){
	float pulse_time = 0.0;
	int ticks = 0;
	char str [128];
	ticks = (8000000 + time_flanco_pos - time_flanco_neg)% 8000000;
	pulse_time = (ticks)/(SysCtlClockGet()/1000000.0);
	return pulse_time;
//	consolePrintStr( 1, 2,"echotime:");
//	sprintf(str," %f us",pulse_time);
//	consolePrintStr( 1,3,str);
//	 refreshConsoleLine(2);
//	 refreshConsoleLine(3);
	//return 1;
}
