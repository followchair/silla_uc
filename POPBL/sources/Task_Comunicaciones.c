#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include "consolaLCD/console.h"
char str_com[128];
int cntComm = 0;

void vTask_Comunicaciones( void *pvParameters ){
	  portTickType xLastWakeTime, period = (portTickType) pvParameters;

	  xLastWakeTime=xTaskGetTickCount();
	  while(1)
	  {

	    cntComm++;

//	    sprintf(str_com,"cnt com.: %d",cnt1);
//	    consolePrintStr(1,9,str_com);
//	    refreshConsoleLine(9);


	    vTaskDelayUntil(&xLastWakeTime, period/portTICK_RATE_MS);
  }
}
