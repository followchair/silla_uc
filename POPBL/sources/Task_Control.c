#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include "consolaLCD/console.h"

void vTask_Control( void *pvParameters ){
	  int i;
	  portTickType xLastWakeTime, period = (portTickType) pvParameters;

	  xLastWakeTime=xTaskGetTickCount();
	  while(1)
	  {


		  for(i=0;i<16000;i++);



	    vTaskDelayUntil(&xLastWakeTime, period/portTICK_RATE_MS);
  }
}
