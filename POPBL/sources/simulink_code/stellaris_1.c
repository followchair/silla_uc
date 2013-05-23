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

#include "stellaris_1.h"
#include "stellaris_1_private.h"

//VARIABLES GLOBALES

real_T Kpx = 1;
real_T Kpy = 15;

/* External inputs (root inport signals with auto storage) */
ExternalInputs_stellaris_1 stellaris_1_U;

/* External outputs (root outports fed by signals with auto storage) */
ExternalOutputs_stellaris_1 stellaris_1_Y;

/* Real-time model */
RT_MODEL_stellaris_1 stellaris_1_M_;
RT_MODEL_stellaris_1 *const stellaris_1_M = &stellaris_1_M_;

/* Model step function */
void stellaris_1_step(void)
{
  boolean_T rtb_Mode;
  real_T rtb_SensorTrasero;
  real_T rtb_SensorDelantero;
  boolean_T rtb_LogicalOperator;
  real_T rtb_DistanciaAsistente;
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

  /* Logic: '<S1>/Logical Operator' incorporates:
   *  Inport: '<Root>/STOP'
   *  RelationalOperator: '<S1>/Relational Operator'
   */
  rtb_LogicalOperator = ((rtb_SensorDelantero == rtb_SensorTrasero) ||
    (stellaris_1_U.STOP));

  /* Switch: '<S3>/Switch' incorporates:
   *  Inport: '<Root>/Sens1'
   *  Inport: '<Root>/Sens4'
   */
  if (rtb_Mode) {
    rtb_Mode_0 = stellaris_1_U.Sens1;
  } else {
    rtb_Mode_0 = stellaris_1_U.Sens4;
  }

  /* Sum: '<S2>/DistanciaAsistente' incorporates:
   *  Constant: '<S2>/ComparacionValorMed'
   */
  rtb_DistanciaAsistente = rtb_Mode_0 - 1.0;

  /* Switch: '<S2>/Switch3' incorporates:
   *  Constant: '<S2>/ComparacionValorMed'
   *  Gain: '<S2>/Kpxneg'
   *  Sum: '<S2>/DistanciaAsistente'
   */
  if (!rtb_Mode) {
    /* Switch: '<S3>/Switch' incorporates:
     *  Inport: '<Root>/Sens1'
     *  Inport: '<Root>/Sens4'
     */
    if (rtb_Mode) {
      rtb_Mode_0 = stellaris_1_U.Sens1;
    } else {
      rtb_Mode_0 = stellaris_1_U.Sens4;
    }

    rtb_DistanciaAsistente = -(rtb_Mode_0 - 1.0);
  }

  /* End of Switch: '<S2>/Switch3' */

  /* Gain: '<S2>/Kpy' incorporates:
   *  Sum: '<S2>/Add'
   */
  rtb_SensorDelantero = (rtb_SensorDelantero - rtb_SensorTrasero) * Kpy;

  /* Switch: '<S2>/Switch2' incorporates:
   *  Switch: '<S2>/Switch1'
   */
  if (rtb_LogicalOperator) {
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
    rtb_Mode_0 = rtb_DistanciaAsistente + rtb_SensorDelantero;

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
    rtb_Mode_0 = rtb_SensorDelantero - rtb_DistanciaAsistente;

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
