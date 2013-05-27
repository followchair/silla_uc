/*****************************************************************************
**											  								**
** project :  POPBL							 							  	**
** filename : pines.h							  							**
** version : 1 									  							**
** date :  	2013-01-16		 		 									    **
** 											  								**
******************************************************************************
** 											  								**
** gpl2 license  2013, Irune Agirre, Aitor Arrieta & Ane Alberdi	  		**
**  								  					                    **
** 											  								**
******************************************************************************
**										        							**
**VERSION HISTORY:									  						**
**----------------									  						**
**Version : 1										  						**
**Date : 2013-01-16										 					**
**Revised by : 							  									**
**Description : Original version.							  				**
*****************************************************************************/
#ifndef _PINES_H
#define _PINES_H
/*****************************************************************************
** 																			**
** MODULES USED 															**
** 																			**
****************************************************************************/
#include "hw_types.h"
#include "hw_memmap.h"
#include "hw_ints.h"
#include "sysctl.h"
#include "interrupt.h"
#include "gpio.h"
#include "FreeRTOS.h"
#include "task.h"
/*****************************************************************************
**	 																		**
** TYPEDEFS AND STRUCTURES 													**
** 																			**
*****************************************************************************/
#ifndef _PINES_C
#define PUB_PINES extern
#else
#define PUB_PINES
#endif

#define PORT_A	1
#define PORT_B	2
#define PORT_C	3
#define PORT_D	4
#define PORT_E	5
#define PORT_F	6
#define PORT_G	7
/*****************************************************************************
**								 											**
** EXPORTED VARIABLES 														**
** 																			**
******************************************************************************/
extern xTaskHandle xHandle_Task_Recibir_Infrarrojos; /*"Handle" de la tarea de
recibir infrarrojos*/
/*****************************************************************************
**					 														**
** EXPORTED FUNCTIONS 														**
** 																			**
******************************************************************************/
void PINES_inicializar(int ulport,int ucPins);
void PINES_inicializar_int_both_edges(int ulport,int ucPins);
/*****************************************************************************
** 																			**
** EOF 																		**
** 																			**
******************************************************************************/
#endif
