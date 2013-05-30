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
#include "driverlib/systick.h"
#include "system_tick.h"
/*********************************************************************
 ** 																**
 ** DEFINITIONS AND MACROS 											**
 ** 																**
 **********************************************************************/
#define TRUE 1
#define LIMITE_OBSTACULO	2900.0 //useg --> Equivalente a 50 cm
#define LIMITE_ESCALON		 406.0 //useg --> Equivalente a  7 cm
/*********************************************************************
** 																	**
** GLOBAL VARIABLES 												**
** 																	**
**********************************************************************/
int time_flanco_pos_obs=0; // Lau hauek globalak nahita nahiez makroa erabiltzeko???
int time_flanco_neg_obs=0;
int time_flanco_pos_esc=0;
int time_flanco_neg_esc=0;
tBoolean flancoPos_Obs = 0;
tBoolean flancoPos_Esc = 0;
tBoolean echo_OK_Obs = 0;
tBoolean echo_OK_Esc = 0;
int g_cycles = 0; /*Ciclos que ha cumplido el Systick*/
extern float gf_uSecho_widht_obs;
extern float gf_uSecho_widht_esc;
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
	 * Se inicializa el PWM 3 para el disparo de los sensores de ultrasonidos
	 */
	ul_periodo_ultrasonid = SysCtlClockGet ()/100; //80ms
	PWM_GENERICO_salida_init(PWM3, ul_periodo_ultrasonid );
	PWM_GENERICO_cambiar_anchura_pulso(0.00025 , PWM3, ul_periodo_ultrasonid); //pulso de 20uS

	/*
	 * Inicializar Pin ECHO para los obstaculos: PD-4 -Input
	 * Habilitar la interrupcion en ambos flancos
	 */
	PINES_inicializar(PORT_D, 4);
	PINES_inicializar_int_both_edges(PORT_D, 4);

	/*
	 * Inicializar Pin ECHO para los escalones: PD-5 -Input //PRUEBA PC7
	 * Habilitar la interrupcion en ambos flancos
	 */
	PINES_inicializar(PORT_C, 7);
	PINES_inicializar_int_both_edges(PORT_C, 7);
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
	unsigned char uc_pin;

	/*
	 * Guardamos el valor de la interrupción
	 */
	long temp = GPIOPinIntStatus(GPIO_PORTD_BASE, TRUE);

//		if ((temp & GPIO_PIN_4)&&(temp & GPIO_PIN_5)){
//			unsigned long estado_pin4;
//			unsigned long estado_pin5;
//			estado_pin4 = GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_4);
//			estado_pin5 = GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_5);
//			estado_pin4 = estado_pin4 & 0x1f;
//			estado_pin5 = estado_pin5 & 0x1f;
//			if ((estado_pin4 == 0x10)&&(estado_pin5 == 0x20)){
//				time_flanco_pos_obs = SYSTEM_TICK_coger_valor_ticks();
//				time_flanco_pos_esc = SYSTEM_TICK_coger_valor_ticks();
//				g_cycles = 0;
//				flancoPos_Obs = 1;
//				flancoPos_Esc = 1;
//			}
//		}

		/*
		 * Miramos si la interrupción ha sido provocada por el pin 0
		 */
		if (temp & GPIO_PIN_4) {
			unsigned long estado_pin;
			uc_pin = GPIO_PIN_4;
			estado_pin = GPIOPinRead(GPIO_PORTD_BASE, uc_pin);
			estado_pin = estado_pin & 0x1f;
			/*
			 * Si el flanco ha sido positivo
			 */
			if (estado_pin == 0x10) {
				time_flanco_pos_obs = SYSTEM_TICK_coger_valor_ticks();
				g_cycles = 0;
				flancoPos_Obs = 1;
			}
			/*
			 * Si el flanco ha sido negativo
			 */
			if (estado_pin == 0x00 && flancoPos_Obs == 1) {
				time_flanco_neg_obs = SYSTEM_TICK_coger_valor_ticks();
				gf_uSecho_widht_obs=TIEMPO_ENTRE_FLANCOS_OBS;
				flancoPos_Obs = 0;
				echo_OK_Obs = 1;
			}
		}
//		if (temp & GPIO_PIN_5) {
//			unsigned long estado_pin;
//			uc_pin = GPIO_PIN_5;
//			estado_pin = GPIOPinRead(GPIO_PORTD_BASE, uc_pin);
//			estado_pin = estado_pin & 0x3f;
//			/*
//			* Si el flanco ha sido positivo
//			*/
//			if (estado_pin == 0x20) {
//				time_flanco_pos_esc = SYSTEM_TICK_coger_valor_ticks();
//				g_cycles = 0;
//				flancoPos_Esc = 1;
//			}
//			/*
//			 * Si el flanco ha sido negativo
//			 */
//			if (estado_pin == 0x00 && flancoPos_Esc == 1) { //PRUEBA
//				time_flanco_neg_esc = SYSTEM_TICK_coger_valor_ticks();
//				gf_uSecho_widht_esc=TIEMPO_ENTRE_FLANCOS_ESC;
//				flancoPos_Esc = 0;
//				echo_OK_Esc = 1;
//			}
//		}
		/*
		 * Limpiamos la interrupción
		 */
		GPIOPinIntClear(GPIO_PORTD_BASE, uc_pin);
}

/**
 * @brief  Rutina de interrupción de los pines del puerto B.
 *
 * @return      -
 *
 * Se mira qué pin ha provocado la interrupción y estado en el que se encuentra ese pin
 * para saber si ha habido un flanco positivo o un flanco negativo.
*/
void __attribute__((interrupt))ULTRASONIDOS_echoInt_PC7(void) {
	unsigned char uc_pin;

	/*
	 * Guardamos el valor de la interrupción
	 */
	long temp = GPIOPinIntStatus(GPIO_PORTC_BASE, TRUE);

		/*
		 * Miramos si la interrupción ha sido provocada por el pin 0
		 */
		if (temp & GPIO_PIN_7) {
			unsigned long estado_pin;
			uc_pin = GPIO_PIN_7;
			estado_pin = GPIOPinRead(GPIO_PORTC_BASE, uc_pin);
			estado_pin = estado_pin & 0xff;
			/*
			 * Si el flanco ha sido positivo
			 */
			if (estado_pin == 0x80) {
				time_flanco_pos_esc = SYSTEM_TICK_coger_valor_ticks();
				g_cycles = 0;
				flancoPos_Esc = 1;
			}
			/*
			 * Si el flanco ha sido negativo
			 */
			if (estado_pin == 0x00 && flancoPos_Esc == 1) {
				time_flanco_neg_esc = SYSTEM_TICK_coger_valor_ticks();
				gf_uSecho_widht_esc=TIEMPO_ENTRE_FLANCOS_ESC;
				flancoPos_Esc = 0;
				echo_OK_Esc = 1;
			}
		}
		/*
		 * Limpiamos la interrupción
		 */
		GPIOPinIntClear(GPIO_PORTC_BASE, uc_pin);
}
/**
 * @brief  Se inicializan los modulos necesarios para los sensores de ultrasonidos
 *
 * @return      -
 *
 * PWM, pines etc.
 */
tBoolean ULTRASONIDOS_obstaculo(float echowidth){
	tBoolean b_obstaculo = 0;

	if( echowidth < LIMITE_OBSTACULO ){
		b_obstaculo = 1;
	}
	return b_obstaculo;
}

/**
 * @brief  Se inicializan los modulos necesarios para los sensores de ultrasonidos
 *
 * @return      -
 *
 * PWM, pines etc.
 */
tBoolean ULTRASONIDOS_escalon(float echowidth){
	tBoolean b_escalon = 0;

	if(( echowidth > LIMITE_ESCALON )||( echowidth < 0.0 )){
		b_escalon = 1;
	}
	return b_escalon;
}
