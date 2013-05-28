#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include "consolaLCD/console.h"

char str_con[128];

void vTask_Control( void *pvParameters ){

	  int i,cnt=0;
	  portTickType xLastWakeTime, period = (portTickType) pvParameters;

	  xLastWakeTime=xTaskGetTickCount();
	  while(1)
	  {
	    for(i=0;i<16000;i++);
	    cnt++;

//	    sprintf(str_con,"cnt control: %d",cnt);
//	    consolePrintStr(1,10,str_con);
//	    refreshConsoleLine(10);


	    vTaskDelayUntil(&xLastWakeTime, period/portTICK_RATE_MS);
  }
}
