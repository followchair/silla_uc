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

extern int echo_OK;
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
	char str[32];
	int i,cnt=0;
	float prueba=0;
	portTickType xLastWakeTime, period = (portTickType) pvParameters;

	xLastWakeTime=xTaskGetTickCount();

	SEGURIDAD_ini();
	while(1)
	{
		for(i=0;i<16000;i++);
	    cnt++;

	    sprintf(str,"cnt Segur: %d",cnt);
	    consolePrintStr(1,10,str);
	    refreshConsoleLine(10);

	    if (echo_OK == 1){
	    	prueba=ULTRASONIDOS_obstaculo();
	    	echo_OK = 0;
	    }
		consolePrintStr( 1, 2,"echotime:");
		sprintf(str," %f us",prueba);
		consolePrintStr( 1,3,str);
		 refreshConsoleLine(2);
		 refreshConsoleLine(3);

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

