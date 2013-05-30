#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include "consolaLCD/console.h"


int cntControl=0;

void vTask_Control( void *pvParameters ){
	  portTickType xLastWakeTime, period = (portTickType) pvParameters;
	  xLastWakeTime=xTaskGetTickCount();

	  while(1)
	  {
	    cntControl++;




	    vTaskDelayUntil(&xLastWakeTime, period/portTICK_RATE_MS);
  }
}
