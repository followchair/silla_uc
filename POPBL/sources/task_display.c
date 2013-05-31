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
#include "display.h"
#include "Recepcion_Infrarrojos.h"
//#include "task_seguridad.h"
//#include "ultrasonidos.h"


/*extern int cntSegur;
extern int cntControl;
extern int cntComm;
extern float distancia_obs;
extern float distancia_esc;
extern tBoolean obstaculo;
extern tBoolean escalon;*/
char str[128],  str1[128],  str2[128],  str3[128],  str4[128],  str5[128],  str6[128],  str7[128];
extern int estado, seguridad=0;
extern float sens1, sens2, sens3, sens4, sens5, sens6, nivel_bateria;
extern int peticion;
extern tBoolean g_parada_seguridad;
extern tBoolean obstaculo;
extern tBoolean escalon;
extern tBoolean bateria;
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
	DISPLAY_inicializar();
	initConsole();
	//consolePrintStr( 1, 1,"Hello POPBL");

	while (1){


		DISPLAY_indicar_estado(estado);
		if(peticion==1){
			DISPLAY_peticion_seguimiento();
		}
	    if(estado==ESPERAR){
	    	FRAME_BUFFER_change_text("										", 3);
	    	FRAME_BUFFER_change_text("										", 4);
	    	FRAME_BUFFER_change_text("												", 5);
	    }
		sprintf(str, "Inf3: %.1f", sens3);
			FRAME_BUFFER_change_text(str, 7);
			//FRAME_BUFFER_write_to_display();
		sprintf(str1, "Inf6: %.1f", sens6);
			FRAME_BUFFER_change_text(str1, 10);
			//FRAME_BUFFER_write_to_display();
		sprintf(str2, "Inf4: %.1f", sens4);
			FRAME_BUFFER_change_text(str2, 8);
			//FRAME_BUFFER_write_to_display();
		sprintf(str3, "Inf1: %.1f", sens1);
			FRAME_BUFFER_change_text(str3, 5);
			//FRAME_BUFFER_write_to_display();
		sprintf(str4, "Inf5: %.1f", sens5);
			FRAME_BUFFER_change_text(str4, 9);
			//FRAME_BUFFER_write_to_display();
			sprintf(str5, "Inf2: %.1f", sens2);
		FRAME_BUFFER_change_text(str5, 6);
		sprintf(str6, "Bat: %.1f", nivel_bateria);
		FRAME_BUFFER_change_text(str6, 11);

		if(g_parada_seguridad == 0){
			seguridad=0;
		}
		else{
			if(obstaculo==1){
				seguridad=1;
			}
			if(escalon == 1){
				seguridad=2;
			}
			if(bateria == 1){
				seguridad = 3;
			}
		}

		sprintf(str7, "Seg: %d", seguridad);
		FRAME_BUFFER_change_text(str7, 12);

		FRAME_BUFFER_write_to_display();

	   // refreshConsole();

		vTaskDelayUntil(&xLastWakeTime, period/portTICK_RATE_MS);
	}
}
