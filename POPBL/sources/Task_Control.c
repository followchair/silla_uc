#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include "consolaLCD/console.h"

void vTask_Control( void *pvParameters ){
	char str[32];
	  int i,cnt=0;
	  portTickType xLastWakeTime, period = (portTickType) pvParameters;

	  xLastWakeTime=xTaskGetTickCount();
	  while(1)
	  {
	    for(i=0;i<16000;i++);
	    cnt++;

	    sprintf(str,"cnt control: %d",cnt);
	    consolePrintStr(1,8,str);
	    refreshConsoleLine(8);


	    vTaskDelayUntil(&xLastWakeTime, period/portTICK_RATE_MS);
  }
}
