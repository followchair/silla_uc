/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"

/* Stellaris library includes. */
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "consolaLCD/console.h"
#include "pwm_generico.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "driverlib/systick.h"

/* The task functions. */
void vTask_Control( void *pvParameters );
void vTask_Comunicaciones( void *pvParameters );
void vTask_Seguridad( void *pvParameters );
void vTask_Display( void *pvParameters );
int main( void )
{
  SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_8MHZ);

	  pwm_init();
  xTaskCreate( vTask_Control,"vTask_Control",200, 1000 , 3, NULL );
  xTaskCreate( vTask_Comunicaciones,"vTask_Comunicaciones",200, 2000 ,2, NULL );
	  stellaris_1_initialize(); //Stellaris
  xTaskCreate( vTask_Seguridad,"vTask_Seguridad",200, 100 , 4, NULL );
  xTaskCreate( vTask_Display,"vTask_Display",200, 200 , 1, NULL );
  vTaskStartScheduler();
  for( ;; );
}


void pwm_init(void){

	PWM_GENERICO_salida_init(PWM4, 20000);
	PWM_GENERICO_salida_init(PWM5, 20000);
}




