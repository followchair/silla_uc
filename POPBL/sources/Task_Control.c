#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include "consolaLCD/console.h"

#include "simulink_code/stellaris_1.h"                /* Model's header file */
#include "simulink_code/rtwtypes.h"                  /* MathWorks types */

double ref_motor1 = 0;
double ref_motor2 = 0;

void rt_OneStep(void);

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

  stellaris_1_U.Sens1 = 0;
  stellaris_1_U.Sens2 = 0;
  stellaris_1_U.Sens3 = 0;
  stellaris_1_U.Sens4 = 0;
  stellaris_1_U.Sens5 = 0;
  stellaris_1_U.Sens6 = 0;
  stellaris_1_U.STOP = false;


  /* Step the model */
  stellaris_1_step();

  /* Get model outputs here */

  ref_motor1  = stellaris_1_Y.Ref_Motor1;
  ref_motor2  = stellaris_1_Y.Ref_Motor2;

  /* Indicate task complete */
  OverrunFlag = FALSE;

  /* Disable interrupts here */
  /* Restore FPU context here (if necessary) */
  /* Enable interrupts here */
}
