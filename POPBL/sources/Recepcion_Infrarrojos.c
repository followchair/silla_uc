/*********************************************************************
 ** 																**
 ** project : POPBL			 										**
 ** filename : Recepcion_Infrarrojos.c								**
 ** version : 1 													**
 ** date : January 16, 2013 										**
 ** 																**
 **********************************************************************
 ** 																**
 ** Copyright (c) 2003, 					 						**
 ** All rights reserved. 											**
 ** 																**
 **********************************************************************
 **																	**
 **VERSION HISTORY:													**
 **----------------													**
 **Version : 1														**
 **Date : January 16, 2013											**
 **Revised by :														**
 **Description : Original version. 									**
 *********************************************************************/
#define _RECEPCION_C_SRC
/*********************************************************************
 **																	**
 ** MODULES USED 													**
 ** 																**
 **********************************************************************/
#include "Recepcion_Infrarrojos.h"
#include "portmacro.h"
#include "systick.h"
#include "framebuffer.h"
#include "stdio.h"
#include "sysctl.h"
#include "gpio.h"
/*********************************************************************
 ** 																**
 ** DEFINITIONS AND MACROS 											**
 ** 																**
 **********************************************************************/
#define FALSE	0
#define TRUE	1
/*Estado esperar*/
ESTADO(esperar)
ITEM_EAC(LEER_ON,RECECPCION_INFRARROJOS_fev_flanco_positivo,RECECPCION_INFRARROJOS_fac_leer_on)
FIN_ESTADO(esperar, ESPERAR, NULL)
/*Estado leer on*/
ESTADO(leer_on)
ITEM_EAC(LEER_ON,RECECPCION_INFRARROJOS_fev_flanco_t_corto_min,RECEPCION_INFRARROJOS_fac_borrar_inter)
ITEM_EAC(LEER_OFF,RECECPCION_INFRARROJOS_fev_flanco_negativo_t_corto_ok,RECECPCION_INFRARROJOS_fac_leer_off)
ITEM_EAC(ESPERAR,RECECPCION_INFRARROJOS_fev_t_corto,RECECPCION_INFRARROJOS_fac_cancelar)
FIN_ESTADO(leer_on, LEER_ON, NULL)
/*Estado leer off*/
ESTADO(leer_off)
ITEM_EAC(LEER_OFF,RECECPCION_INFRARROJOS_fev_flanco_t_largo_min,RECEPCION_INFRARROJOS_fac_borrar_inter)
ITEM_EAC(LEER_ON_2,RECECPCION_INFRARROJOS_fev_flanco_positivo_t_largo_ok,RECECPCION_INFRARROJOS_fac_leer_on_2)
ITEM_EAC(ESPERAR,RECECPCION_INFRARROJOS_fev_t_largo,RECECPCION_INFRARROJOS_fac_cancelar)
FIN_ESTADO(leer_off, LEER_OFF, NULL)
/*Estado leer on 2*/
ESTADO(leer_on_2)
ITEM_EAC(LEER_ON_2,RECECPCION_INFRARROJOS_fev_flanco_t_largo_min,RECEPCION_INFRARROJOS_fac_borrar_inter)
ITEM_EAC(LEER_OFF_2,RECECPCION_INFRARROJOS_fev_flanco_negativo_t_largo_ok,RECECPCION_INFRARROJOS_fac_leer_off_2)
ITEM_EAC(ESPERAR,RECECPCION_INFRARROJOS_fev_t_largo,RECECPCION_INFRARROJOS_fac_cancelar)
FIN_ESTADO(leer_on_2, LEER_ON_2, NULL)
/*Estado leer off 2*/
ESTADO(leer_off_2)
ITEM_EAC(LEER_OFF_2,RECECPCION_INFRARROJOS_fev_flanco_t_corto_min,RECEPCION_INFRARROJOS_fac_borrar_inter)
ITEM_EAC(PREGUNTAR,RECECPCION_INFRARROJOS_fev_flanco_positivo_t_corto_ok,RECECPCION_INFRARROJOS_fac_preguntar)
ITEM_EAC(ESPERAR,RECECPCION_INFRARROJOS_fev_t_corto,RECECPCION_INFRARROJOS_fac_cancelar)
FIN_ESTADO(leer_off_2, LEER_OFF_2, NULL)
/*Estado preguntar*/
ESTADO(preguntar)
ITEM_EAC(ACTIVADO,RECECPCION_INFRARROJOS_fev_derecha_pulsado,RECECPCION_INFRARROJOS_fac_activar)
ITEM_EAC(ESPERAR,RECECPCION_INFRARROJOS_fev_izquierda_pulsado,RECECPCION_INFRARROJOS_fac_cancelar)
FIN_ESTADO(preguntar, PREGUNTAR, NULL)
/*Estado activado*/
ESTADO(activado)
ITEM_EAC(LEER_OFF_3,RECECPCION_INFRARROJOS_fev_flanco_negativo,RECECPCION_INFRARROJOS_fac_leer_off_3)
ITEM_EAC(ACTIVADO,RECECPCION_INFRARROJOS_fev_comunicacion_activada,RECECPCION_INFRARROJOS_fac_medir_senal)
ITEM_EAC(PERDIDA_SENAL,RECECPCION_INFRARROJOS_fev_comunicacion_perdida,RECECPCION_INFRARROJOS_fac_indicar_perdida)
FIN_ESTADO(activado, ACTIVADO, NULL)
/*Estado perdida de la señal*/
ESTADO(perdida_senal)
ITEM_EAC(ACTIVADO,RECECPCION_INFRARROJOS_fev_comunicacion_recuperada,RECECPCION_INFRARROJOS_fac_activar)
FIN_ESTADO(perdida_senal, PERDIDA_SENAL, NULL)
/*Estado leer off 3*/
ESTADO(leer_off_3)
ITEM_EAC(LEER_OFF_3,RECECPCION_INFRARROJOS_fev_flanco_t_corto_min,RECEPCION_INFRARROJOS_fac_borrar_inter)
ITEM_EAC(LEER_ON_3,RECECPCION_INFRARROJOS_fev_flanco_positivo_t_corto_ok,RECECPCION_INFRARROJOS_fac_leer_on_3)
ITEM_EAC(ACTIVADO,RECECPCION_INFRARROJOS_fev_t_corto,RECECPCION_INFRARROJOS_fac_activar)
FIN_ESTADO(leer_off_3, LEER_OFF_3, NULL)
/*Estado leer on 3*/
ESTADO(leer_on_3)
ITEM_EAC(LEER_ON_3,RECECPCION_INFRARROJOS_fev_flanco_t_largo_min,RECEPCION_INFRARROJOS_fac_borrar_inter)
ITEM_EAC(LEER_OFF_4,RECECPCION_INFRARROJOS_fev_flanco_negativo_t_largo_ok,RECECPCION_INFRARROJOS_fac_leer_off_4)
ITEM_EAC(ACTIVADO,RECECPCION_INFRARROJOS_fev_t_largo,RECECPCION_INFRARROJOS_fac_activar)
FIN_ESTADO(leer_on_3, LEER_ON_3, NULL)
/*Estado leer off 4*/
ESTADO(leer_off_4)
ITEM_EAC(LEER_OFF_4,RECECPCION_INFRARROJOS_fev_flanco_t_largo_min,RECEPCION_INFRARROJOS_fac_borrar_inter)
ITEM_EAC(LEER_ON_4,RECECPCION_INFRARROJOS_fev_flanco_positivo_t_largo_ok,RECECPCION_INFRARROJOS_fac_leer_on_4)
ITEM_EAC(ACTIVADO,RECECPCION_INFRARROJOS_fev_t_largo,RECECPCION_INFRARROJOS_fac_activar)
FIN_ESTADO(leer_off_4, LEER_OFF_4, NULL)
/*Estado leer on 4*/
ESTADO(leer_on_4)
ITEM_EAC(LEER_ON_4,RECECPCION_INFRARROJOS_fev_flanco_t_corto_min,RECEPCION_INFRARROJOS_fac_borrar_inter)
ITEM_EAC(ESPERAR,RECECPCION_INFRARROJOS_fev_flanco_negativo_t_corto_ok,RECECPCION_INFRARROJOS_fac_desactivar)
ITEM_EAC(ACTIVADO,RECECPCION_INFRARROJOS_fev_t_corto,RECECPCION_INFRARROJOS_fac_activar)
FIN_ESTADO(leer_on_4, LEER_ON_4, NULL)
/*Definimos la máquina de estados para activar y desactivar la comunicación*/
AUTOMATA(activar_infrarrojos)
&esperar, &
leer_on, &
leer_off, &
leer_on_2, &
leer_off_2, &preguntar,
&activado,
&perdida_senal,
&leer_off_3,
&leer_on_3,
&leer_off_4,
&leer_on_4
FIN_AUTOMATA(activar_infrarrojos,ACTIVAR_INFRARROJOS, NULL)
/*********************************************************************
 ** 																**
 ** GLOBAL VARIABLES 												**
 ** 																**
 **********************************************************************/
unsigned long g_ul_xTimeTimerOn;	/*VaValor del systick al detectar un flanco*/
unsigned long g_ul_xTimeTimerOff1; /*Valor del systick a la espera de un nuevo flanco*/
portTickType g_xTimeFlanco;/*Valor de los ticks del FreeRTOS*/
float g_time = 0; /*Tiempo transcurrido*/
int g_cycles = 0; /*Ciclos que ha cumplido el Systick*/
char str[32], str1[32], str2[32], str3[32], str4[32], str5[32]; /*Var. para guardar el texto a escribir*/
extern xTaskHandle xHandle_Task_Recibir_Infrarrojos; /*"Handle" de la tarea
 de recepcion de infrarrojos*/
tBoolean g_comunicacion_activada=FALSE;
extern float sens1, sens2, sens3, sens4, sens5, sens6;
int estado = 0, peticion = 0;

/*********************************************************************
 ** 																**
 ** LOCAL FUNCTIONS 												**
 ** 																**
 **********************************************************************/
/**
 * @brief  Evento que se da cuando hay un flanco positivo.
 *
 * @return 	boolean
 *
 * Coge el valor de la variable que se activa en la rutina de interrupción
 * y lo devuelve, haciendo que el evento sea TRUE o FALSE.
 */
tBoolean RECECPCION_INFRARROJOS_fev_flanco_positivo(void) {
	tBoolean a;
	a = RECEPCION_INFRARROJOS_mirar_flanco_positivo();
	return a;
}
/**
 * @brief  Evento que se da si el tiempo transcurrido desde el último flanco es
 * demasiado corto.
 *
 * @return 	boolean
 *
 * Mira la diferencia de los tiempos del último flanco y el momento actual, y devuelve
 * un TRUE si es demasiado corto y un FALSE si no lo es.
 */
tBoolean RECECPCION_INFRARROJOS_fev_flanco_t_corto_min(void) {
	g_ul_xTimeTimerOff1 = SYSTEM_TICK_coger_valor_ticks();
	if ((TIEMPO_ENTRE_FLANCOS) < T_95_MS)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}

}
/**
 * @brief  Evento que se da cuando el tiempo transcurrido desde el último flanco es
 * correcto.
 *
 * @return 	boolean
 *
 * Coge el valor de la variable que se activa en la rutina de interrupción, mira si el
 * tiempo transcurrido desde el último flanco es correcto y en el caso de que lo sea
 * devuelve el valor de la variable g_arriba.
 */
tBoolean RECECPCION_INFRARROJOS_fev_flanco_positivo_t_corto_ok(void) {
	tBoolean a;
	a = RECEPCION_INFRARROJOS_mirar_flanco_positivo();
	g_ul_xTimeTimerOff1 = SYSTEM_TICK_coger_valor_ticks();
	if (((TIEMPO_ENTRE_FLANCOS) > T_95_MS) && ((TIEMPO_ENTRE_FLANCOS)< T_105_MS))
	{
		return a;
	}
	else
	{
		return FALSE;
	}

}
/**
 * @brief  Evento que se da cuando el tiempo transcurrido desde el último flanco es
 * demasiado corto.
 *
 * @return 	boolean
 *
 * Mira la diferencia de los tiempos del último flanco y el momento actual, y devuelve
 * un TRUE si es demasiado corto y un FALSE si no lo es.
 */
tBoolean RECECPCION_INFRARROJOS_fev_flanco_t_largo_min(void) {
	g_ul_xTimeTimerOff1 = SYSTEM_TICK_coger_valor_ticks();

	if ((TIEMPO_ENTRE_FLANCOS) < T_195_MS)
	{
		return TRUE;
	} else
	{
		return FALSE;
	}

}
/**
 * @brief  Evento que se da cuando el tiempo transcurrido desde el último flanco es
 * correcto.
 *
 * @return 	boolean
 *
 * Coge el valor de la variable que se activa en la rutina de interrupción, mira si el
 * tiempo transcurrido desde el último flanco es correcto y en el caso de que lo sea
 * devuelve el valor de la variable g_arriba.
 */
tBoolean RECECPCION_INFRARROJOS_fev_flanco_positivo_t_largo_ok(void) {
	tBoolean a;
	a = RECEPCION_INFRARROJOS_mirar_flanco_positivo();
	g_ul_xTimeTimerOff1 = SYSTEM_TICK_coger_valor_ticks();

	if (((TIEMPO_ENTRE_FLANCOS) > T_195_MS) && ((TIEMPO_ENTRE_FLANCOS)< T_205_MS))
	{
		return a;
	}
	else
	{
		return FALSE;
	}

}
/**
 * @brief  Evento que se da cuando hay un flanco negativo.
 *
 * @return 	boolean
 *
 * Coge el valor de la variable que se activa en la rutina de interrupción
 * y lo devuelve, haciendo que el evento sea TRUE o FALSE.
 */
tBoolean RECECPCION_INFRARROJOS_fev_flanco_negativo(void) {
	tBoolean a;
	a = RECEPCION_INFRARROJOS_mirar_flanco_negativo();
	return a;
}
/**
 * @brief  Evento que se da cuando el tiempo transcurrido desde el último flanco es
 * correcto.
 *
 * @return 	boolean
 *
 * Coge el valor de la variable que se activa en la rutina de interrupción, mira si el
 * tiempo transcurrido desde el último flanco es correcto y en el caso de que lo sea
 * devuelve el valor de la variable g_arriba.
 */
tBoolean RECECPCION_INFRARROJOS_fev_flanco_negativo_t_corto_ok(void) {
	tBoolean a;
	a = RECEPCION_INFRARROJOS_mirar_flanco_negativo();
	g_ul_xTimeTimerOff1 = SYSTEM_TICK_coger_valor_ticks();
	if (((TIEMPO_ENTRE_FLANCOS) > T_95_MS) && ((TIEMPO_ENTRE_FLANCOS)< T_105_MS))
	{
		return a;
	}
	else
	{
		return FALSE;
	}
}
/**
 * @brief  Evento que se da cuando el tiempo transcurrido desde el último flanco es
 * correcto.
 *
 * @return 	boolean
 *
 * Coge el valor de la variable que se activa en la rutina de interrupción, mira si el
 * tiempo transcurrido desde el último flanco es correcto y en el caso de que lo sea
 * devuelve el valor de la variable g_arriba.
 */
tBoolean RECECPCION_INFRARROJOS_fev_flanco_negativo_t_largo_ok(void) {
	tBoolean a;
	a = RECEPCION_INFRARROJOS_mirar_flanco_negativo();
	g_ul_xTimeTimerOff1 = SYSTEM_TICK_coger_valor_ticks();
	if (((TIEMPO_ENTRE_FLANCOS) > T_195_MS) && ((TIEMPO_ENTRE_FLANCOS)< T_205_MS))
	{
		return a;
	}
	else
	{
		return FALSE;
	}
}
/**
 * @brief  Evento que se da cuando se pulsa el botón izquierdo.
 *
 * @return 	boolean
 *
 * Coge el valor de la variable que se activa en la rutina de interrupción y lo
 * devuelve haciendo que el evento sea TRUE o FALSE.
 */
tBoolean RECECPCION_INFRARROJOS_fev_izquierda_pulsado() {
	tBoolean a;
	a = g_izquierda;
	g_izquierda = 0;
	return a;
}
/**
 * @brief  Evento que se da cuando se pulsa el botón derecho.
 *
 * @return 	boolean
 *
 * Coge el valor de la variable que se activa en la rutina de interrupción y lo
 * devuelve haciendo que el evento sea TRUE o FALSE.
 */
tBoolean RECECPCION_INFRARROJOS_fev_derecha_pulsado() {
	tBoolean a;
	a = g_derecha;
	g_derecha = 0;
	return a;
}
/**
 * @brief  Acción que se realiza al entrar en el primer estado.
 *
 * @return 	-
 *
 * Escribe en la pantalla el estado en el que se encuentra, coge el valor del
 * systick y hace dormir la tarea durante 90ms.
 */
void RECECPCION_INFRARROJOS_fac_leer_on(void) {

	estado = LEER_ON;
	RECEPCION_INFRARROJOS_coger_tiempo_actual();
	RECEPCION_INFRARROJOS_dormir_tarea_90ms();

}
/**
 * @brief  Acción que se realiza al entrar en el segundo estado.
 *
 * @return 	-
 *
 * Escribe en la pantalla el estado en el que se encuentra, coge el valor del
 * systick y hace dormir la tarea durante 190ms.
 */
void RECECPCION_INFRARROJOS_fac_leer_off(void) {

	estado = LEER_OFF;
	RECEPCION_INFRARROJOS_coger_tiempo_actual();
	RECEPCION_INFRARROJOS_dormir_tarea_190ms();

}
/**
 * @brief  Acción que se realiza al entrar en el tercer estado.
 *
 * @return 	-
 *
 * Escribe en la pantalla el estado en el que se encuentra, coge el valor del
 * systick y hace dormir la tarea durante 190ms.
 */
void RECECPCION_INFRARROJOS_fac_leer_on_2(void) {
	estado = LEER_ON_2;
	RECEPCION_INFRARROJOS_coger_tiempo_actual();
	RECEPCION_INFRARROJOS_dormir_tarea_190ms();
}
/**
 * @brief  Acción que se realiza al entrar en el cuarto estado.
 *
 * @return 	-
 *
 * Escribe en la pantalla el estado en el que se encuentra, coge el valor del
 * systick y hace dormir la tarea durante 90ms.
 */
void RECECPCION_INFRARROJOS_fac_leer_off_2(void) {

	estado = LEER_OFF_2;
	RECEPCION_INFRARROJOS_coger_tiempo_actual();
	RECEPCION_INFRARROJOS_dormir_tarea_90ms();
}
/**
 * @brief  Acción que se realiza al entrar en el cuarto estado de desconexión.
 *
 * @return 	-
 *
 * Escribe en la pantalla el estado en el que se encuentra, coge el valor del
 * systick y hace dormir la tarea durante 90ms.
 */
void RECECPCION_INFRARROJOS_fac_leer_on_4(void) {

	estado = LEER_ON_4;
	RECEPCION_INFRARROJOS_coger_tiempo_actual();
	RECEPCION_INFRARROJOS_dormir_tarea_90ms();
}
/**
 * @brief  Acción que se realiza al entrar en el primer estado de desconexión.
 *
 * @return 	-
 *
 * Escribe en la pantalla el estado en el que se encuentra, coge el valor del
 * systick y hace dormir la tarea durante 90ms.
 */
void RECECPCION_INFRARROJOS_fac_leer_off_3(void) {

	estado = LEER_OFF_3;
	RECEPCION_INFRARROJOS_coger_tiempo_actual();
	RECEPCION_INFRARROJOS_dormir_tarea_90ms();
}
/**
 * @brief  Acción que se realiza al entrar en el segundo estado de desconexión.
 *
 * @return 	-
 *
 * Escribe en la pantalla el estado en el que se encuentra, coge el valor del
 * systick y hace dormir la tarea durante 190ms.
 */
void RECECPCION_INFRARROJOS_fac_leer_on_3(void) {

	estado = LEER_ON_3;
	RECEPCION_INFRARROJOS_coger_tiempo_actual();
	RECEPCION_INFRARROJOS_dormir_tarea_190ms();
}
/**
 * @brief  Acción que se realiza al entrar en el tercer estado de desconexión.
 *
 * @return 	-
 *
 * Escribe en la pantalla el estado en el que se encuentra, coge el valor del
 * systick y hace dormir la tarea durante 190ms.
 */
void RECECPCION_INFRARROJOS_fac_leer_off_4(void) {

	estado = LEER_OFF_4;
	RECEPCION_INFRARROJOS_coger_tiempo_actual();
	RECEPCION_INFRARROJOS_dormir_tarea_190ms();
}
/**
 * @brief  Acción que se realiza al activar la comunicación.
 *
 * @return 	-
 *
 * Escribe en la pantalla que se ha establecido la comunicación.
 */
void RECECPCION_INFRARROJOS_fac_activar(void) {
	peticion = 0;
	estado = ACTIVADO;
	g_comunicacion_activada = TRUE;
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 1);

}
/**
 * @brief  Acción que se realiza al desactivar la comunicación.
 *
 * @return 	-
 *
 * Escribe en la pantalla que se ha desactivado la comunicación y suspende la tarea.
 */
void RECECPCION_INFRARROJOS_fac_desactivar(void) {

	estado = ESPERAR;
	g_comunicacion_activada = FALSE;
	sens1 = 0.0;
	sens2 = 0.0;
	sens3 = 0.0;
	sens4 = 0.0;
	sens5 = 0.0;
	sens6 = 0.0;
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 0);
	vTaskSuspend(xHandle_Task_Recibir_Infrarrojos);
}
/**
 * @brief  Evento que se da cuando el tiempo transcurrido desde el último flanco es
 * demasiado largo (mayor que 105 ms).
 *
 * @return 	boolean
 *
 * Escribe en la pantalla que se ha establecido la comunicación.
 */
tBoolean RECECPCION_INFRARROJOS_fev_t_corto(void) {
	g_ul_xTimeTimerOff1 = SYSTEM_TICK_coger_valor_ticks();
	if ((TIEMPO_ENTRE_FLANCOS) > T_105_MS) {
		return TRUE;
	} else {
		return FALSE;
	}

}
/**
 * @brief  Evento que se da cuando el tiempo transcurrido desde el último flanco es
 * demasiado largo (mayor que 205 ms).
 *
 * @return 	boolean
 *
 * Escribe en la pantalla que se ha establecido la comunicación.
 */
tBoolean RECECPCION_INFRARROJOS_fev_t_largo(void) {
	g_ul_xTimeTimerOff1 = SYSTEM_TICK_coger_valor_ticks();
	if ((TIEMPO_ENTRE_FLANCOS) > T_205_MS) {
		return TRUE;
	} else {
		return FALSE;
	}

}
/**
 * @brief  Acción que se realiza cuando se cancela el intento de activar la
 * comunicación.
 *
 * @return 	-
 *
 * Escribe en la pantalla que está en espera y suspende la tarea.
 */
void RECECPCION_INFRARROJOS_fac_cancelar(void) {
	peticion = 0;
	estado = ESPERAR;
	vTaskSuspend(xHandle_Task_Recibir_Infrarrojos);
}
/**
 * @brief  Acción que borra todos los flancos detectados hasta el momento.
 *
 * @return 	-
 *
 * Borra las variables que se activan con las interrupciones de los flancos.
 */
void RECEPCION_INFRARROJOS_fac_borrar_inter(void) {
	g_abajo = 0; /*Anulau oain arteko interrupziyuk*/
	g_arriba = 0;
}
/**
 * @brief  Acción que escribe en pantalla la petición de activar el seguimiento.
 *
 * @return 	-
 *
 */
void RECECPCION_INFRARROJOS_fac_preguntar(void) {
	estado = PREGUNTAR;
	peticion = 1;
}
/**
 * @brief  Coge el valor del tiempo actual.
 *
 * @return 	-
 *
 * Coge el valor del systick del momento actual, reinicia la variable que cuenta
 * los ciclos que ha acabdo el systick y coge el valor de los ticks del momento
 * del FreeRTOS.
 *
 */
void RECEPCION_INFRARROJOS_coger_tiempo_actual() {
	g_ul_xTimeTimerOn = SYSTEM_TICK_coger_valor_ticks();
	g_cycles = 0;
	g_xTimeFlanco = xTaskGetTickCount();
}
/**
 * @brief  Hace que la tarea se duerma durante 190ms.
 *
 * @return 	-
 *
 */
void RECEPCION_INFRARROJOS_dormir_tarea_190ms() {
	vTaskDelayUntil(&g_xTimeFlanco, TICKS_190MS);
}
/**
 * @brief  Hace que la tarea se duerma durante 90ms.
 *
 * @return 	-
 *
 */
void RECEPCION_INFRARROJOS_dormir_tarea_90ms() {
	vTaskDelayUntil(&g_xTimeFlanco, TICKS_90MS);
}
/**
 * @brief  Función que devuelve el valor de la variable que se activa con
 * un flanco positivo.
 *
 * @return 	Boolean
 *
 */
tBoolean RECEPCION_INFRARROJOS_mirar_flanco_positivo() {
	tBoolean a;
	a = g_arriba;
	g_arriba = 0;
	return a;
}
/**
 * @brief  Función que devuelve el valor de la variable que se activa con
 * un flanco negativo.
 *
 * @return 	Boolean
 *
 */
tBoolean RECEPCION_INFRARROJOS_mirar_flanco_negativo() {
	tBoolean a;
	a = g_abajo;
	g_abajo = 0;
	return a;
}

tBoolean RECECPCION_INFRARROJOS_fev_comunicacion_activada(){
	return g_comunicacion_activada;
}
tBoolean RECECPCION_INFRARROJOS_fev_comunicacion_perdida(){
	//if ((sens1 < SENAL_MINIMA) && (sens2 < SENAL_MINIMA) && (sens3 < SENAL_MINIMA) && (sens4 < SENAL_MINIMA) && (sens5 < SENAL_MINIMA) && (sens6 < SENAL_MINIMA)){
	if ((sens1 < 0.5) && (sens2 < 0.5) && (sens3 < 0.5) && (sens4 < 0.5) && (sens5 < 0.5) && (sens6 < 0.5)){
	return true;
	}
	else{
		return false;
	}
}
tBoolean RECECPCION_INFRARROJOS_fev_comunicacion_recuperada(){
	RECECPCION_INFRARROJOS_fac_medir_senal();
	if ((sens1 > 0.5) || (sens2 > 0.5) || (sens3 > 0.5) || (sens4 > 0.5) || (sens5 > 0.5) || (sens6 > 0.5)){
		return true;
	}
	else{
		RECECPCION_INFRARROJOS_fac_indicar_perdida();
		return false;

	}
}
void RECECPCION_INFRARROJOS_fac_indicar_perdida(){
	estado = PERDIDA_SENAL;
	sens1 = 0.0;
	sens2 = 0.0;
	sens3 = 0.0;
	sens4 = 0.0;
	sens5 = 0.0;
	sens6 = 0.0;
}
void RECECPCION_INFRARROJOS_fac_medir_senal(){

/*Activamos el MUX analógico y seleccionamos las entradas de los sensores 1 y 4*/
	GPIOPinWrite(GPIO_PORTG_BASE, GPIO_PIN_0, 0); /*INH=0*/
	GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_5, 0); /*A=0*/
	GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7, 0); /*B=0*/


	sens4= AD_ObtenerValorADC_Channel2();
	sens1= AD_ObtenerValorADC_Channel3();


	/*Seleccionamos las entradas de los sensores 2 y 5*/
	GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_5, 32); /*A=1*/
	//GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7, 0); /*B=0*/


	sens5= AD_ObtenerValorADC_Channel2();
	sens2= AD_ObtenerValorADC_Channel3();


	/*Seleccionamos las entradas de los sensores 3 y 6*/
	GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_5, 0); /*A=0*/
	GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7, 128); /*B=1*/



	sens6= AD_ObtenerValorADC_Channel2();
	sens3= AD_ObtenerValorADC_Channel3();

	/*Desactivamos el MUX*/
	GPIOPinWrite(GPIO_PORTG_BASE, GPIO_PIN_0, 1); /*INH=1*/

}
/*********************************************************************
 ** 																	**
 ** EOF 																**
 ** 																	**
 **********************************************************************/
