/*****************************************************************************
**											  								**
** project :  POPBL							 							  	**
** filename : ultrasonidos.h	  				  							**
** version : 1 									  							**
** date :  	2013-05-26		 		 									    **
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
**Date : 2013-05-26										 					**
**Revised by : 							  									**
**Description : Original version.							  				**
*****************************************************************************/
#ifndef _ULTRASONIDOS_H
#define _ULTRASONIDOS_H
/*****************************************************************************
** 																			**
** MODULES USED 															**
** 																			**
****************************************************************************/
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "hw_ints.h"
#include "interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "pines.h"
#include "pwm_generico.h"
#include "stdio.h"

#define		PERIODO		8000.0
#define		TICKS_ENTRE_FLANCOS		time_flanco_pos - time_flanco_neg + g_cycles*PERIODO
#define		TIEMPO_ENTRE_FLANCOS	(TICKS_ENTRE_FLANCOS*1000.0)/(PERIODO); // en uSeg
/*****************************************************************************
**					 														**
** EXPORTED FUNCTIONS 														**
** 																			**
******************************************************************************/
void ULTRASONIDOS_ini(void);
tBoolean ULTRASONIDOS_obstaculo(float echowidth);
/*****************************************************************************
** 																			**
** EOF 																		**
** 																			**
******************************************************************************/
#endif
