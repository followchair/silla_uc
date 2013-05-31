/*********************************************************************
** 																	**
** project : PFinal_Vitroceramica									**
** filename : pwm_generico.c										**
** version : 1 														**
** date : December 19, 2012											**
** 																	**
**********************************************************************
** 																	**
** Copyright (c) 2012, Irune Agirre Troncoso						**
** All rights reserved. 											**
** 																	**
**********************************************************************
**																	**
**VERSION HISTORY:													**
**----------------													**
**Version : 1														**
**Date : December 19, 2012											**
**Revised by : ---													**
**Description : Original version. 									**
*********************************************************************/

#define _PWM_GENERICO_C_SRC

/*********************************************************************
**																	**
** MODULES USED 													**
** 																	**
**********************************************************************/
#include "pwm_generico.h"

/*********************************************************************
** 																	**
** GLOBAL VARIABLES 												**
** 																	**
**********************************************************************/
static unsigned long pwmOutput[6]={PWM_OUT_0, PWM_OUT_1, /*!< Array con los posibles PWM */
									PWM_OUT_2, PWM_OUT_3,
									PWM_OUT_4, PWM_OUT_5};

static unsigned long pwmOutput_bit[6]={PWM_OUT_0_BIT, PWM_OUT_1_BIT, /*!< Array con las 	 */
										PWM_OUT_2_BIT,	PWM_OUT_3_BIT, /* posibles salidas PWM */
										PWM_OUT_4_BIT, PWM_OUT_5_BIT};

//static unsigned long int g_ul_pulses_period;

/*********************************************************************
** 																	**
** LOCAL FUNCTIONS 													**
** 																	**
**********************************************************************/
/**
 * @brief  Función para inicializar cualquier PWM del Stellaris LM3S8962
 *
 * @return  void
 *
 *
*/
void PWM_GENERICO_salida_init(int OutputPin, unsigned long g_ul_pulses_period){
	int pwm_gen; /*!< Guarda el generador PWM a utilizar */

	// Habilitamos el periférico PWM y establecemos su reloj
	SysCtlPWMClockSet(SYSCTL_PWMDIV_8);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM);

	/* Habilitamos los pines de salida segun el PWM a utilizar
	 seleccionando el generador adecuado para cada PWM */
	switch(OutputPin)
		{
			  case 0:
			  {
					//pin GPIO PF0 para el PWM0
					SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
					GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_0);
					pwm_gen=PWM_GEN_0; //Generador 0
					//Establece el periodo
					PWMGenPeriodSet (PWM_BASE, pwm_gen, g_ul_pulses_period);
			  }break;
			  case 1:
			  {
					//pin GPIO PG1 para el PWM1
					SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOG);
					GPIOPinTypePWM(GPIO_PORTG_BASE, GPIO_PIN_1);
					pwm_gen=PWM_GEN_0; //Generador 0
					//Establece el periodo
					PWMGenPeriodSet (PWM_BASE, pwm_gen, g_ul_pulses_period);
			  }break;
			  case 2:
			  {
				  //pin GPIO PB0 para el PWM2
					SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
					GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_0);
					pwm_gen=PWM_GEN_1;//Generador 1
					//Establece el periodo
					PWMGenPeriodSet (PWM_BASE, pwm_gen, g_ul_pulses_period);
			  }break;
			  case 3:
			  {
				  //pin GPIO PB1 para el PWM3
					SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
					GPIOPinTypePWM (GPIO_PORTB_BASE, GPIO_PIN_1);
					pwm_gen=PWM_GEN_1;//Generador 1
					//Establece el periodo
					PWMGenPeriodSet (PWM_BASE, pwm_gen, g_ul_pulses_period);
			  }break;
			  case 4:
			  {
				  //pin GPIO PE0 para el PWM4
					SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
					GPIOPinTypePWM (GPIO_PORTE_BASE, GPIO_PIN_0);
					pwm_gen=PWM_GEN_2;//Generador 4
					//Establece el periodo
					PWMGenPeriodSet (PWM_BASE, pwm_gen, g_ul_pulses_period);
			  }break;
			  case 5:
			  {
				  //pin GPIO PE1 para el PWM1
					SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
					GPIOPinTypePWM (GPIO_PORTE_BASE, GPIO_PIN_1);
					pwm_gen=PWM_GEN_2;//Generador 2
					//Establece el periodo
					PWMGenPeriodSet (PWM_BASE, pwm_gen, g_ul_pulses_period);
			  }break;
		}

	// Configurar el generador
	PWMGenConfigure (PWM_BASE, pwm_gen, PWM_GEN_MODE_UP_DOWN | PWM_GEN_MODE_NO_SYNC);

	// Establecer el periodo
//	g_ul_pulses_period = SysCtlClockGet ()/100;//IRUNE aldauta ultrasoinutzako
//	PWMGenPeriodSet (PWM_BASE, pwm_gen, g_ul_pulses_period);

	//Comenzar los timer del generador PWM seleccionado
	PWMGenEnable (PWM_BASE, pwm_gen);
}
/**
 * @brief  Función para cambiar la anchura del pulso PWM
 *
 * @return void
 *
 *
*/
void PWM_GENERICO_cambiar_anchura_pulso(float width, int OutputPin, unsigned long g_ul_pulses_period){

	PWMPulseWidthSet (PWM_BASE, pwmOutput[OutputPin], g_ul_pulses_period * width);

	// Activar la salida
	PWMOutputState (PWM_BASE, pwmOutput_bit[OutputPin], true);
}
/*********************************************************************
** 																	**
** EOF 																**
** 																	**
**********************************************************************/
