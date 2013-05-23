#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include "consolaLCD/console.h"

void vTask_Comunicaciones( void *pvParameters ){
	char str[32];
	  int i,cnt1=0;
	  portTickType xLastWakeTime, period = (portTickType) pvParameters;

	  xLastWakeTime=xTaskGetTickCount();
	  while(1)
	  {
	    for(i=0;i<16000;i++);
	    cnt1++;

	    sprintf(str,"cnt com.: %d",cnt1);
	    consolePrintStr(1,6,str);
	    refreshConsoleLine(6);


	    vTaskDelayUntil(&xLastWakeTime, period/portTICK_RATE_MS);
  }
}
