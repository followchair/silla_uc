/*********************************************************************
** 																	**
** project : POPBL			 										**
** filename : task_seguridad.c										**
** version : 1 														**
** date : May, 27, 2013 											**
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
**Date : May, 27, 2013												**
**Revised by :														**
**Description : Original version. 									**
*********************************************************************/
#define _TASK_SEGURIDAD_C_SRC
/*********************************************************************
**																	**
** MODULES USED 													**
** 																	**
**********************************************************************/
#include "FreeRTOS.h"
#include "task.h"
#include "task_seguridad.h"
#include "ultrasonidos.h"
#include "ad.h"

float gf_uSecho_widht_obs=0;
float gf_uSecho_widht_esc=0;
float nivel_bateria=0;
extern tBoolean echo_OK_Obs;
extern tBoolean echo_OK_Esc;
int cntSegur =0;
float distancia_obs = 0;
float distancia_esc = 0;
tBoolean obstaculo = 0;
tBoolean escalon = 0;
tBoolean bateria = 0;
tBoolean g_parada_seguridad = 0;

#define MIN_BATERIA	5.0
/*********************************************************************
** 																	**
** LOCAL FUNCTIONS 													**
** 																	**
**********************************************************************/
/**
 * @brief  Tarea encargada de la seguridad
 *
 * @return      -
 *
 * Ultrasonidos
*/
void vTask_Seguridad( void *pvParameters ){

	portTickType xLastWakeTime, period = (portTickType) pvParameters;
	xLastWakeTime=xTaskGetTickCount();

	SEGURIDAD_ini();

	while(1)
	{
	    cntSegur++;

	    if (echo_OK_Obs == 1){
	    	obstaculo = ULTRASONIDOS_obstaculo(gf_uSecho_widht_obs);
	    	distancia_obs = gf_uSecho_widht_obs / 58.0;
	    	echo_OK_Obs = 0;
	    }

	    if (echo_OK_Esc == 1){
	   	    escalon = ULTRASONIDOS_escalon(gf_uSecho_widht_esc);
	   	    distancia_esc = gf_uSecho_widht_esc / 58.0;
	   	    echo_OK_Esc = 0;
	   	}
	    /*Hacer la conversión ADC del nivel de batería*/
//		GPIOPinWrite(GPIO_PORTG_BASE, GPIO_PIN_0, 0); /*INH=0*/
//		GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_5, 0); /*A=0*/
//		GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7, 0); /*B=0*/

		nivel_bateria= AD_ObtenerValorADC_Channel1();

		if (nivel_bateria <= MIN_BATERIA){
			bateria = 1;
		}
		else
		{
			bateria=0;
		}

//		GPIOPinWrite(GPIO_PORTG_BASE, GPIO_PIN_0, 1); /*INH=1*/

	    /*	Mirar si hay alguna emergencia para que la silla se pare	*/
	    if ((obstaculo == 1)||(escalon == 1)/*||(bateria == 1)*/)	g_parada_seguridad = 1;
	    else 	g_parada_seguridad = 0;

	    vTaskDelayUntil(&xLastWakeTime, period/portTICK_RATE_MS);
  }
}

/**
 * @brief  Se inicializan los modulos necesarios para las funciones de seguridad
 *
 * @return      -
 *
 * PWM, pines etc.
 */
void SEGURIDAD_ini(void){
	ULTRASONIDOS_ini();
}

