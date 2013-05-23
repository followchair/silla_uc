/*****************************************************************************
**											  								**
** project :  PFinal_Vitroceramica			 							  	**
** filename : pwm_generico.h  							  					**
** version : 1 									  							**
** date :  	2012-12-19		 		 									    **
** 											  								**
******************************************************************************
** 											  								**
** gpl2 license  2012, Irune Agirre	Troncoso						  		**
**  								  					                    **
** 											  								**
******************************************************************************
**										        							**
**VERSION HISTORY:									  						**
**----------------									  						**
**Version : 1										  						**
**Date : 2012-12-19										 					**
**Revised by : 							  									**
**Description : Original version.							  				**
*****************************************************************************/

#ifndef _PWM_GENERICO_H
#define _PWM_GENERICO_H

/*****************************************************************************
** 																			**
** MODULES USED 															**
** 																			**
****************************************************************************/
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/pwm.h"
#include "inc/hw_pwm.h"
#include "gpio.h"

/*****************************************************************************
** 																			**
** DEFINITIONS AND MACROS 													**
** 																			**
******************************************************************************/
#define PWM0_LED 0
#define PWM1_SOUND 1
#define PWM2 2
#define PWM3 3
#define PWM4 4
#define PWM5 5

/*****************************************************************************
** 																			**
** PROTOTYPES OF GLOBAL FUNCTIONS											**
** 																			**
******************************************************************************/
void PWM_GENERICO_salida_init(int OutputPin, unsigned long g_ul_pulses_period);
void PWM_GENERICO_cambiar_anchura_pulso(float width, int OutputPin, unsigned long g_ul_pulses_period);

/*****************************************************************************
** 																			**
** EOF 																		**
** 																			**
******************************************************************************/
#endif
