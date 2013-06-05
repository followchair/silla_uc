/*********************************************************************
** 																	**
** project : POPBL			 										**
** filename : display.c												**
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
#define _DISPLAY_C_SRC
/*********************************************************************
**																	**
** MODULES USED 													**
** 																	**
**********************************************************************/
#include "display.h"
/*********************************************************************
** 																	**
** LOCAL FUNCTIONS 													**
** 																	**
**********************************************************************/
/**
 * @brief  Inicialización del display.
 *
 * @return      -
 *
 * Se inicializa el Frame Buffer y se escribe en pantalla.
*/
void DISPLAY_inicializar() {
	/*
	 * Se inicializa la pantalla y el framebuffer
	 */
	FRAME_BUFFER_init();
	/*
	 * Se escribe en el framebuffer
	 */
	FRAME_BUFFER_insert_text("Hello POPBL", 25, 1); //id=0
	FRAME_BUFFER_insert_text("	", 1, 10); //id=1
	FRAME_BUFFER_insert_text("		", 1, 20); //id=2
	FRAME_BUFFER_insert_text("		", 1, 30); //id=3
	FRAME_BUFFER_insert_text("		", 1, 40); //id=4


	FRAME_BUFFER_insert_text("				", 1, 50); //id=5
	FRAME_BUFFER_insert_text("				", 1, 60); //id=6
	FRAME_BUFFER_insert_text("				", 1, 70); //id=7
	FRAME_BUFFER_insert_text("	 			", 65, 50); //id=8
	FRAME_BUFFER_insert_text("	 			", 65, 60); //id=9
	FRAME_BUFFER_insert_text("	 			", 65, 70); //id=10

	FRAME_BUFFER_insert_text("	 			", 1, 80); //id=11
	FRAME_BUFFER_insert_text("	 			", 65, 80); //id=12*/
	/*
	 * Se vuelcan todos los elementos a la pantalla
	 */
	FRAME_BUFFER_write_to_display();
}
/**
 * @brief  Se escribe el texto correspondiente a cada estado en la pantalla.
 *
 * @return      -
 *
 * Se escribe en el FrameBuffer el texto que indica el estado.
*/
void DISPLAY_indicar_estado(int state) {
	char *texto; /*Variable que guarda el texto a escribir en cada caso*/
	/*
	 * Se coge el texto a escribir
	 */
	switch (state) {
	case 0: /*Estado "esperar"*/
		texto = "en espera							";
		break;
	case 1: /*Estado "leyendo on"*/
		texto = "leyendo on							";
		break;
	case 2: /*Estado "leyendo off"*/
		texto = "leyendo off						";
		break;
	case 3: /*Estado "leyendo on 2"*/
		texto = "leyendo on 2						";
		break;
	case 4: /*Estado "leyendo off 2"*/
		texto = "leyendo off 2						";
		break;
	case 5: /*Estado "preguntar"*/
		texto = "			    						";
		break;
	case 6: /*Estado "activado"*/
		texto = "activado							";
		break;
	case 7: /*Estado "leyendo off 3"*/
		texto = "leyendo off 3						";
		break;
	case 8: /*Estado "leyendo on 3"*/
		texto = "leyendo on 3						";
		break;
	case 9: /*Estado "leyendo off 4"*/
		texto = "leyendo off 4						";
		break;
	case 10: /*Estado "leyendo on 4"*/
		texto = "leyendo on 4						";
		break;
	case 11: /*Estado "señal perdida4"*/
			texto = "Perdida de la señal						";
			break;
	}
	/*
	 * Se escribe en el framebuffer
	 */
	FRAME_BUFFER_change_text(texto, 1);
//	FRAME_BUFFER_change_text("																				", 2);
//	FRAME_BUFFER_change_text("																		", 3);
//	FRAME_BUFFER_change_text("																		", 4);



/*	FRAME_BUFFER_change_text("																				", 5);
	FRAME_BUFFER_change_text("																		", 6);
	FRAME_BUFFER_change_text("																		", 7);
	FRAME_BUFFER_change_text("																				", 8);
	FRAME_BUFFER_change_text("																		", 9);
	FRAME_BUFFER_change_text("																		", 10);
	FRAME_BUFFER_change_text("																				", 11);
	FRAME_BUFFER_change_text("																		", 12);
*/
/*
	 * Se vuelca en la pantalla
	 */
	FRAME_BUFFER_write_to_display();
}
/**
 * @brief  Escribe en pantalla la petición de seguimiento.
 *
 * @return      -
 *
 *
*/
void DISPLAY_peticion_seguimiento() {
	/*
	 * Se escriben la pregunta y las opciones en el framebuffer
	 */
	FRAME_BUFFER_change_text("activar seguimiento?	", 2); //id=2
	FRAME_BUFFER_change_text("izq: desactivar						", 3); //id=3
	FRAME_BUFFER_change_text("dcha: activar							", 4); //id=4

}
/*********************************************************************
** 																	**
** EOF 																**
** 																	**
**********************************************************************/
