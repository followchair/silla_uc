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
#include <stdio.h>
#include "consolaLCD/console.h"
#include "task_seguridad.h"
#include "ultrasonidos.h"

int tiempoObs = 56000; // PROBATZEKO, gero borratu
float prueba=0;
extern int echo_OK;
extern int time_flanco_pos;
extern int time_flanco_neg;
extern int g_cycles; /*Ciclos que ha cumplido el Systick*/
char str_segur[128];
char str1[128];
char str2[128];
char str3[32];
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

	int i,cnt=0;
	tBoolean obstaculo = 0;
	//float prueba=0;
	int prueba2=0;
	float distancia = 0;
	portTickType xLastWakeTime, period = (portTickType) pvParameters;

	xLastWakeTime=xTaskGetTickCount();

	SEGURIDAD_ini();
	while(1)
	{

	    cnt++;

	    sprintf(str_segur,"cnt Segur: %d",cnt);
	    consolePrintStr(1,11,str_segur);
	    refreshConsoleLine(11);


//	    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_5, 0x20);
//	    for(i=0;i<tiempoObs;i++);
//	    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_5, 0x00);

	    if (echo_OK == 1){
	   // 	prueba=ULTRASONIDOS_obstaculo();
	    	prueba2 = TICKS_ENTRE_FLANCOS;
	    //	prueba=TIEMPO_ENTRE_FLANCOS;
	    	obstaculo = ULTRASONIDOS_obstaculo(prueba);
	    	echo_OK = 0;
	    }

	    distancia = prueba / 58.0;

		consolePrintStr( 1, 2,"echotime:");
		sprintf(str1," %.2f us",prueba);
		consolePrintStr( 1,3,str1);
		 refreshConsoleLine(2);
		 refreshConsoleLine(3);

		 sprintf(str2,"distan: %.2f cm", distancia);
		 		consolePrintStr( 1,4,str2);
		 		 refreshConsoleLine(4);

		 		sprintf(str3,"Obstaculo: %d ",obstaculo);
		 				 		consolePrintStr( 1,6,str3);
		 				 		 refreshConsoleLine(6);

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

	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	  GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_5);
	  GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_5, 0x00);
	ULTRASONIDOS_ini();

}

