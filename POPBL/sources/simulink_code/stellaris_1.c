/*
 * File: stellaris_1.c
 *
 * Code generated for Simulink model 'stellaris_1'.
 *
 * Model version                  : 1.17
 * Simulink Coder version         : 8.2 (R2012a) 29-Dec-2011
 * TLC version                    : 8.2 (Dec 29 2011)
 * C/C++ source code generated on : Thu May 23 13:58:38 2013
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

/**
 * @file    stellaris_1.c
 * @brief   Codigo necesario para realizar el control proporcional de la posicion del robot
 * @author  Ane Alberdi
 * @author  Irune Agirre
 * @author  Aitor Arrieta
 * @date    2013-05-23
 * @todo 	Calibrar variables de control (Kpx y Kpy)
 */

/*---------------------------------------------------------------*/
/*-------------------Librerias necesarias -----------------------*/
/*---------------------------------------------------------------*/
#include "stellaris_1.h"
#include "stellaris_1_private.h"

/*---------------------------------------------------------------*/
/*------------------- Variables Globales -----------------------*/
/*---------------------------------------------------------------*/

real_T Kpx = 3;
real_T Kpy = 5;

/* External inputs (root inport signals with auto storage) */
ExternalInputs_stellaris_1 stellaris_1_U;

/* External outputs (root outports fed by signals with auto storage) */
ExternalOutputs_stellaris_1 stellaris_1_Y;

/* Real-time model */
RT_MODEL_stellaris_1 stellaris_1_M_;
RT_MODEL_stellaris_1 *const stellaris_1_M = &stellaris_1_M_;



/**
 * @brief   Control proporcional del robot
 * @par		Logica
 *			- Selecciona la informacion util de los sensores
 *			- Control proporcional eje X
 *			- Control proporcional eje Y
 * @param
 * @return  void
 */
/* Model step function */
void stellaris_1_step(void)
{
  boolean_T rtb_Mode;
  real_T rtb_SensorTrasero;
  real_T rtb_SensorDelantero;
  real_T rtb_DistanciaAsistente;
  real_T rtb_Switch3;
  real_T rtb_Mode_0;

  /* RelationalOperator: '<S3>/Relational Operator' incorporates:
   *  Inport: '<Root>/Sens1'
   *  Inport: '<Root>/Sens4'
   */
  rtb_Mode = (stellaris_1_U.Sens1 > stellaris_1_U.Sens4);

  /* Switch: '<S3>/Switch1' incorporates:
   *  Inport: '<Root>/Sens2'
   *  Inport: '<Root>/Sens3'
   *  Inport: '<Root>/Sens5'
   *  Inport: '<Root>/Sens6'
   *  Switch: '<S3>/Switch2'
   */
  if (rtb_Mode) {
    rtb_SensorDelantero = stellaris_1_U.Sens2;
    rtb_SensorTrasero = stellaris_1_U.Sens3;
  } else {
    rtb_SensorDelantero = stellaris_1_U.Sens5;
    rtb_SensorTrasero = stellaris_1_U.Sens6;
  }

  /* End of Switch: '<S3>/Switch1' */

  /* Switch: '<S3>/Switch' incorporates:
   *  Inport: '<Root>/Sens1'
   *  Inport: '<Root>/Sens4'
   */
  if (rtb_Mode) {
    rtb_Mode_0 = stellaris_1_U.Sens1;
  } else {
    rtb_Mode_0 = stellaris_1_U.Sens4;
  }

  /* End of Switch: '<S3>/Switch' */

  /* Switch: '<S2>/Switch3' incorporates:
   *  Constant: '<S2>/ComparacionValorMed'
   *  Gain: '<S2>/Kpx'
   *  Gain: '<S2>/Kpxneg'
   *  Sum: '<S2>/DistanciaAsistente'
   */
  if (rtb_Mode) {
    rtb_Switch3 = (rtb_Mode_0 - 1.0) * Kpx;
  } else {
    rtb_Switch3 = (rtb_Mode_0 - 1.0) * (-Kpx);
  }

  /* End of Switch: '<S2>/Switch3' */

  /* Gain: '<S2>/Kpy' incorporates:
   *  Sum: '<S2>/Add'
   */
  rtb_DistanciaAsistente = (rtb_SensorDelantero - rtb_SensorTrasero) * Kpy;

  /* Switch: '<S2>/Switch2' incorporates:
   *  Inport: '<Root>/STOP'
   *  Logic: '<S1>/Logical Operator'
   *  RelationalOperator: '<S1>/Relational Operator'
   *  Switch: '<S2>/Switch1'
   */
  if ((rtb_SensorDelantero == rtb_SensorTrasero) || (stellaris_1_U.STOP)) {
    /* Outport: '<Root>/Ref_Motor1' incorporates:
     *  Constant: '<S2>/Constant3'
     */
    stellaris_1_Y.Ref_Motor1 = 0.0;

    /* Outport: '<Root>/Ref_Motor2' incorporates:
     *  Constant: '<S2>/Constant1'
     */
    stellaris_1_Y.Ref_Motor2 = 0.0;
  } else {
    /* Sum: '<S2>/Add1' */
    rtb_Mode_0 = rtb_Switch3 + rtb_DistanciaAsistente;

    /* Saturate: '<S2>/Saturation' */
    if (rtb_Mode_0 >= 10.0) {
      /* Outport: '<Root>/Ref_Motor1' */
      stellaris_1_Y.Ref_Motor1 = 10.0;
    } else if (rtb_Mode_0 <= -10.0) {
      /* Outport: '<Root>/Ref_Motor1' */
      stellaris_1_Y.Ref_Motor1 = -10.0;
    } else {
      /* Outport: '<Root>/Ref_Motor1' */
      stellaris_1_Y.Ref_Motor1 = rtb_Mode_0;
    }

    /* End of Saturate: '<S2>/Saturation' */

    /* Sum: '<S2>/Add2' */
    rtb_Mode_0 = rtb_DistanciaAsistente - rtb_Switch3;

    /* Saturate: '<S2>/Saturation1' */
    if (rtb_Mode_0 >= 10.0) {
      /* Outport: '<Root>/Ref_Motor2' */
      stellaris_1_Y.Ref_Motor2 = 10.0;
    } else if (rtb_Mode_0 <= -10.0) {
      /* Outport: '<Root>/Ref_Motor2' */
      stellaris_1_Y.Ref_Motor2 = -10.0;
    } else {
      /* Outport: '<Root>/Ref_Motor2' */
      stellaris_1_Y.Ref_Motor2 = rtb_Mode_0;
    }

    /* End of Saturate: '<S2>/Saturation1' */
  }

  /* End of Switch: '<S2>/Switch2' */
}




/**
 * @brief   Inicializaciones del control
 * @param
 * @return  void
 */
/* Model initialize function */
void stellaris_1_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(stellaris_1_M, (NULL));

  /* external inputs */
  (void) memset((void *)&stellaris_1_U, 0,
                sizeof(ExternalInputs_stellaris_1));

  /* external outputs */
  (void) memset((void *)&stellaris_1_Y, 0,
                sizeof(ExternalOutputs_stellaris_1));
}


/**
 * @brief   Codigo para terminar el control -> No necesario, pero tal vez en el futuro si
 * @param
 * @return  void
 */
/* Model terminate function */
void stellaris_1_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
