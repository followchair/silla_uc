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
/*****************************************************************************
**					 														**
** EXPORTED FUNCTIONS 														**
** 																			**
******************************************************************************/
void ULTRASONIDOS_ini(void);
float ULTRASONIDOS_obstaculo(void);
/*****************************************************************************
** 																			**
** EOF 																		**
** 																			**
******************************************************************************/
#endif
