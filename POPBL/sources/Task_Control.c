/**
 * @file    Task_Control.c
 * @brief   Codigo necesario para realizar el control de la posicion del robot
 * @par		Logica
 *			-Tarea del sistema operativo de tiempo real FreeRTOS, que se activa cada X
 *			-Dicha tarea hace una llamada a una funcion que controla el robot haciendo uso de
 *			codigo generado por Simulink
 * @author  Ane Alberdi
 * @author  Irune Agirre
 * @author  Sir. Aitor Arrieta
 * @date    2013-05-28
 */


/*---------------------------------------------------------------*/
/*-------------------Librerias necesarias -----------------------*/
/*---------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include "consolaLCD/console.h"
#include "simulink_code/stellaris_1.h"                /* Model's header file */
#include "simulink_code/rtwtypes.h"                  /* MathWorks types */
#include "pwm_generico.h"


/*---------------------------------------------------------------*/
/*------------------Variables Globales --------------------------*/
/*---------------------------------------------------------------*/
double ref_motor1 = 0;
double ref_motor2 = 0;
unsigned long int periodo = 20000;
float duty1 = 0;
float duty2 = 0;
extern tBoolean g_parada_seguridad;

/*---------------------------------------------------------------*/
/*------------------Funciones privadas --------------------------*/
/*---------------------------------------------------------------*/
void rt_OneStep(void);



/**
 * @brief   Tarea que realiza el control de posicion del robot respecto al dispositivo guia
 * @par		Logica
 *			- Inicializaciones necesarias
 *			- Llamada a funcion rt_OneStep();
 *			- Refrescar pantalla
 * @param
 * @return  void
 */
void vTask_Control( void *pvParameters ){
	char str[32];
	  int i,cnt=0;
	  portTickType xLastWakeTime, period = (portTickType) pvParameters;

	  xLastWakeTime=xTaskGetTickCount();

	  while(1)
	  {

		rt_OneStep();
	    for(i=0;i<16000;i++);
	    cnt++;

	    sprintf(str,"cnt control: %d",cnt);
	    consolePrintStr(1,8,str);
	    refreshConsoleLine(8);


	    vTaskDelayUntil(&xLastWakeTime, period/portTICK_RATE_MS);
  }
}



/**
 * @brief   Funcion que realiza el control de posicion del robot respecto al dispositivo guia
 * 			Parte del codigo es generado por Simulink
 * @par		Logica
 *			- Inicializaciones necesaria
 *			- Se recoge la informacion de los sensores
 *			- Se llama a la funcion stellaris_1_step(); -> Control proporcional de los motores
 *			- Se guarda la referencia de los motores
 *			- Se calcula el duty cycle del pwm para cada motor
 *			- Se genera la señal PWM que va a los motores
 *
 * @param
 * @return  void
 */
void rt_OneStep(void)
{
  static boolean_T OverrunFlag = 0;

  /* Disable interrupts here */

  /* Check for overrun */
  if (OverrunFlag) {
    rtmSetErrorStatus(stellaris_1_M, "Overrun");
    return;
  }

  OverrunFlag = TRUE;

  /* Save FPU context here (if necessary) */
  /* Re-enable timer or interrupt here */
  /* Set model inputs here */


//@todo asignar a cada variable su sensor (al juntar programa con el de ane)


  stellaris_1_U.Sens1 = 0;
  stellaris_1_U.Sens2 = 0;
  stellaris_1_U.Sens3 = 0;
  stellaris_1_U.Sens4 = 0;
  stellaris_1_U.Sens5 = 0;
  stellaris_1_U.Sens6 = 0;
  stellaris_1_U.STOP = g_parada_seguridad;
//  i = 1;



  /* Step the model */
  stellaris_1_step();

  /* Get model outputs here */

  ref_motor1  = stellaris_1_Y.Ref_Motor1;
  ref_motor2  = stellaris_1_Y.Ref_Motor2;

  /* Indicate task complete */
  OverrunFlag = FALSE;

  /* Control motor PWM*/

  /*Calculo de los duty cycles -> uno tiene malda positiva y la otra negativa, ya que lo motores
  en el robot estan invertidos*/
  duty1 = 0.001*ref_motor1 + 1.5/20;
  duty2 = -0.001*ref_motor2 + 1.5/20;

  /* Activar PWM*/


  PWM_GENERICO_salida_init(PWM4, periodo);
  PWM_GENERICO_salida_init(PWM5, periodo);

  PWM_GENERICO_cambiar_anchura_pulso(duty1, PWM4, periodo);
  PWM_GENERICO_cambiar_anchura_pulso(duty2, PWM5, periodo);

  /* Disable interrupts here */
  /* Restore FPU context here (if necessary) */
  /* Enable interrupts here */
}
