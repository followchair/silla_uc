/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"

/* Stellaris library includes. */
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "consolaLCD/console.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>




/* The task functions. */
void vTask_Control( void *pvParameters );
void vTask_Comunicaciones( void *pvParameters );
int main( void )
{
  SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_8MHZ);
  initConsole();
  consolePrintStr( 1, 1,"Hello POPBL");
  refreshConsoleLine(1);
  xTaskCreate( vTask_Control,"vTask_Control",200, 1000 ,1, NULL );
  xTaskCreate( vTask_Comunicaciones,"vTask_Comunicaciones",200, 2000 ,2, NULL );
  vTaskStartScheduler();
  for( ;; );
}





