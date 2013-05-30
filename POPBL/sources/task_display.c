/*********************************************************************
** 																	**
** project : POPBL			 										**
** filename : task_display.c										**
** version : 1 														**
** date : May, 29, 2013 											**
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
**Date : May, 29, 2013												**
**Revised by :														**
**Description : Original version. 									**
*********************************************************************/
#define _TASK_DISPLAY_C_SRC
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


extern int cntSegur;
extern int cntControl;
extern int cntComm;
extern float distancia_obs;
extern float distancia_esc;
extern tBoolean obstaculo;
extern tBoolean escalon;
extern tBoolean g_parada_seguridad;
char str[128];
/*********************************************************************
** 																	**
** LOCAL FUNCTIONS 													**
** 																	**
**********************************************************************/
/**
 * @brief  Tarea encargada de escribir en la pantalla
 *
 * @return      -
 *
 *
*/
void vTask_Display( void *pvParameters ){

	portTickType xLastWakeTime, period = (portTickType) pvParameters;
	xLastWakeTime=xTaskGetTickCount();
	initConsole();
	consolePrintStr( 1, 1,"Hello POPBL");

	while (1){

//		consolePrintStr( 1, 2,"echotime:");
//		sprintf(str," %.2f us",gf_uSecho_widht);
//		consolePrintStr( 1,3,str);

		sprintf(str,"Obstaculo: %d ",obstaculo);
		consolePrintStr( 1,2,str);

		sprintf(str,"distan: %.2f cm", distancia_obs);
		consolePrintStr( 1,3,str);

		sprintf(str,"Escalon: %d ",escalon);
		consolePrintStr( 1,5,str);

		sprintf(str,"distan: %.2f cm", distancia_esc);
		consolePrintStr( 1,6,str);

		sprintf(str,"Emerg: %d ", g_parada_seguridad);
		consolePrintStr( 1,7,str);

		sprintf(str,"cnt com.: %d",cntComm);
		consolePrintStr(1,9,str);

		sprintf(str,"cnt control: %d",cntControl);
		consolePrintStr(1,10,str);

	    sprintf(str,"cnt Segur: %d",cntSegur);
	    consolePrintStr(1,11,str);

	    refreshConsole();

		vTaskDelayUntil(&xLastWakeTime, period/portTICK_RATE_MS);
	}
}
