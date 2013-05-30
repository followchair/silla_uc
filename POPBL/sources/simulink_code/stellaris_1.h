/*
 * File: stellaris_1.h
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

#ifndef RTW_HEADER_stellaris_1_h_
#define RTW_HEADER_stellaris_1_h_
#ifndef stellaris_1_COMMON_INCLUDES_
# define stellaris_1_COMMON_INCLUDES_
//#include <stddef.h>
#include <string.h>
#include "rtwtypes.h"
//#include "rtw_continuous.h"
//#include "rtw_solver.h"
#endif                                 /* stellaris_1_COMMON_INCLUDES_ */

#include "stellaris_1_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* External inputs (root inport signals with auto storage) */
typedef struct {
  real_T Sens1;                        /* '<Root>/Sens1' */
  real_T Sens2;                        /* '<Root>/Sens2' */
  real_T Sens3;                        /* '<Root>/Sens3' */
  real_T Sens4;                        /* '<Root>/Sens4' */
  real_T Sens5;                        /* '<Root>/Sens5' */
  real_T Sens6;                        /* '<Root>/Sens6' */
  boolean_T STOP;                      /* '<Root>/STOP' */
} ExternalInputs_stellaris_1;

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  real_T Ref_Motor1;                   /* '<Root>/Ref_Motor1' */
  real_T Ref_Motor2;                   /* '<Root>/Ref_Motor2' */
} ExternalOutputs_stellaris_1;

/* Real-time Model Data Structure */
struct RT_MODEL_stellaris_1 {
  const char_T * volatile errorStatus;
};

/* External inputs (root inport signals with auto storage) */
extern ExternalInputs_stellaris_1 stellaris_1_U;

/* External outputs (root outports fed by signals with auto storage) */
extern ExternalOutputs_stellaris_1 stellaris_1_Y;

/* Model entry point functions */
extern void stellaris_1_initialize(void);
extern void stellaris_1_step(void);
extern void stellaris_1_terminate(void);

/* Real-time Model object */
extern struct RT_MODEL_stellaris_1 *const stellaris_1_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'stellaris_1'
 * '<S1>'   : 'stellaris_1/Stellaris'
 * '<S2>'   : 'stellaris_1/Stellaris/Control Posicion'
 * '<S3>'   : 'stellaris_1/Stellaris/SeleccionSensores'
 */
#endif                                 /* RTW_HEADER_stellaris_1_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
