/*
 * sfuntmpl_basic.c: Basic 'C' template for a level 2 S-function.
 *
 * Copyright 1990-2013 The MathWorks, Inc.
 */


/*
 * You must specify the S_FUNCTION_NAME as the name of your S-function
 * (i.e. replace sfuntmpl_basic with the name of your S-function).
 */

#define S_FUNCTION_NAME  can_read
#define S_FUNCTION_LEVEL 2

/*
 * Need to include simstruc.h for the definition of the SimStruct and
 * its associated macro definitions.
 */
#include "simstruc.h"

#include <stdio.h>
#include "controlcan.h"


#define DEV_IDX 20
unsigned int handle;

/* Error handling
 * --------------
 *
 * You should use the following technique to report errors encountered within
 * an S-function:
 *
 *       ssSetErrorStatus(S,"Error encountered due to ...");
 *       return;
 *
 * Note that the 2nd argument to ssSetErrorStatus must be persistent memory.
 * It cannot be a local variable. For example the following will cause
 * unpredictable errors:
 *
 *      mdlOutputs()
 *      {
 *         char msg[256];         {ILLEGAL: to fix use "static char msg[256];"}
 *         sprintf(msg,"Error due to %s", string);
 *         ssSetErrorStatus(S,msg);
 *         return;
 *      }
 *
 */

/*====================*
 * S-function methods *
 *====================*/

/* Function: mdlInitializeSizes ===============================================
 * Abstract:
 *    The sizes information is used by Simulink to determine the S-function
 *    block's characteristics (number of inputs, outputs, states, etc.).
 */
static void mdlInitializeSizes(SimStruct *S)
{
    ssSetNumSFcnParams(S, 0);  /* Number of expected parameters */
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
        /* Return if number of expected != number of actual parameters */
        return;
    }

    ssSetNumContStates(S, 0);
    ssSetNumDiscStates(S, 0);

    if (!ssSetNumInputPorts(S, 1)) return;
    ssSetInputPortWidth(S, 0, 1);
    ssSetInputPortDataType(S, 0, SS_UINT32);
    ssSetInputPortRequiredContiguous(S, 0, true); /*direct input signal access*/
    /*
     * Set direct feedthrough flag (1=yes, 0=no).
     * A port has direct feedthrough if the input is used in either
     * the mdlOutputs or mdlGetTimeOfNextVarHit functions.
     */
    ssSetInputPortDirectFeedThrough(S, 0, 1);

    if (!ssSetNumOutputPorts(S, 17)) return;
    ssSetOutputPortWidth(S, 0, 8);
    ssSetOutputPortWidth(S, 1, 8);
    ssSetOutputPortWidth(S, 2, 8);
    ssSetOutputPortWidth(S, 3, 8);
    ssSetOutputPortWidth(S, 4, 8);
    ssSetOutputPortWidth(S, 5, 8);
    ssSetOutputPortWidth(S, 6, 8);
    ssSetOutputPortWidth(S, 7, 8);    
    ssSetOutputPortWidth(S, 8, 8);
    ssSetOutputPortWidth(S, 9, 8);
    ssSetOutputPortWidth(S, 10, 8);
    ssSetOutputPortWidth(S, 11, 8);
    ssSetOutputPortWidth(S, 12, 8);
    ssSetOutputPortWidth(S, 13, 8);
    ssSetOutputPortWidth(S, 14, 8);
    ssSetOutputPortWidth(S, 15, 8);      
    ssSetOutputPortWidth(S, 16, 8);

    ssSetOutputPortDataType(S, 0, SS_UINT8);
    ssSetOutputPortDataType(S, 1, SS_UINT8);
    ssSetOutputPortDataType(S, 2, SS_UINT8);
    ssSetOutputPortDataType(S, 3, SS_UINT8);
    ssSetOutputPortDataType(S, 4, SS_UINT8);
    ssSetOutputPortDataType(S, 5, SS_UINT8);
    ssSetOutputPortDataType(S, 6, SS_UINT8);
    ssSetOutputPortDataType(S, 7, SS_UINT8);
    ssSetOutputPortDataType(S, 8, SS_UINT8);
    ssSetOutputPortDataType(S, 9, SS_UINT8);
    ssSetOutputPortDataType(S, 10, SS_UINT8);
    ssSetOutputPortDataType(S, 11, SS_UINT8);
    ssSetOutputPortDataType(S, 12 , SS_UINT8);
    ssSetOutputPortDataType(S, 13, SS_UINT8);
    ssSetOutputPortDataType(S, 14, SS_UINT8);
    ssSetOutputPortDataType(S, 15, SS_UINT8);
    ssSetOutputPortDataType(S, 16, SS_UINT8);
    
    ssSetNumSampleTimes(S, 1);
    ssSetNumRWork(S, 0);
    ssSetNumIWork(S, 0);
    ssSetNumPWork(S, 0);
    ssSetNumModes(S, 0);
    ssSetNumNonsampledZCs(S, 0);

    /* Specify the sim state compliance to be same as a built-in block */
    ssSetSimStateCompliance(S, USE_DEFAULT_SIM_STATE);

    ssSetOptions(S, 0);
}



/* Function: mdlInitializeSampleTimes =========================================
 * Abstract:
 *    This function is used to specify the sample time(s) for your
 *    S-function. You must register the same number of sample times as
 *    specified in ssSetNumSampleTimes.
 */
static void mdlInitializeSampleTimes(SimStruct *S)
{
    ssSetSampleTime(S, 0, 0.02);
    ssSetOffsetTime(S, 0, 0.0);

}



#define MDL_INITIALIZE_CONDITIONS   /* Change to #undef to remove function */
#if defined(MDL_INITIALIZE_CONDITIONS)
  /* Function: mdlInitializeConditions ========================================
   * Abstract:
   *    In this function, you should initialize the continuous and discrete
   *    states for your S-function block.  The initial states are placed
   *    in the state vector, ssGetContStates(S) or ssGetRealDiscStates(S).
   *    You can also perform any other initialization activities that your
   *    S-function may require. Note, this routine will be called at the
   *    start of simulation and if it is present in an enabled subsystem
   *    configured to reset states, it will be call when the enabled subsystem
   *    restarts execution to reset the states.
   */
  static void mdlInitializeConditions(SimStruct *S)
  {


    
      
  }
#endif /* MDL_INITIALIZE_CONDITIONS */



#define MDL_START  /* Change to #undef to remove function */
#if defined(MDL_START) 
  /* Function: mdlStart =======================================================
   * Abstract:
   *    This function is called once at start of model execution. If you
   *    have states that should be initialized once, this is the place
   *    to do it.
   */
  static void mdlStart(SimStruct *S)
  {
  }
#endif /*  MDL_START */



/* Function: mdlOutputs =======================================================
 * Abstract:
 *    In this function, you compute the outputs of your S-function
 *    block.
 */
static void mdlOutputs(SimStruct *S, int_T tid)
{
    const uint32_T *u = (const uint32_T *) ssGetInputPortSignal(S,0);
    uint8_T       *y0 = (uint8_T *) ssGetOutputPortSignal(S,0);
    uint8_T       *y1 = (uint8_T *) ssGetOutputPortSignal(S,1);
    uint8_T       *y2 = (uint8_T *) ssGetOutputPortSignal(S,2);
    uint8_T       *y3 = (uint8_T *) ssGetOutputPortSignal(S,3);
    uint8_T       *y4 = (uint8_T *) ssGetOutputPortSignal(S,4);
    uint8_T       *y5 = (uint8_T *) ssGetOutputPortSignal(S,5);
    uint8_T       *y6 = (uint8_T *) ssGetOutputPortSignal(S,6);
    uint8_T       *y7 = (uint8_T *) ssGetOutputPortSignal(S,7);
    uint8_T       *y8 = (uint8_T *) ssGetOutputPortSignal(S,8);
    uint8_T       *y9 = (uint8_T *) ssGetOutputPortSignal(S,9);
    uint8_T       *y10 = (uint8_T *) ssGetOutputPortSignal(S,10);
    uint8_T       *y11 = (uint8_T *) ssGetOutputPortSignal(S,11);
    uint8_T       *y12 = (uint8_T *) ssGetOutputPortSignal(S,12);
    uint8_T       *y13 = (uint8_T *) ssGetOutputPortSignal(S,13);
    uint8_T       *y14 = (uint8_T *) ssGetOutputPortSignal(S,14);
    uint8_T       *y15 = (uint8_T *) ssGetOutputPortSignal(S,15);
    uint8_T       *y16 = (uint8_T *) ssGetOutputPortSignal(S,16);    
    
   unsigned int hd;
    
	PVCI_CAN_OBJ msg;
    int i;
    int num=0;
    DWORD temp_id;
    uint8_T temp_data[8];
    uint8_T temp_len;
    
    // mapping can with ZS11
    if (u[0] >0) {
        
         hd = VCI_Receive(DEV_IDX, 0, 0, msg, 100, 10);
         if (hd >0) {

             printf("handle is %u\n", hd);
            for(num=0;num<hd;num++) {
                temp_id =( *(msg+num)).ID;
                temp_len = 8;
                for(i=0;i<8;i++) {
                    temp_data[i] =( *(msg+num)).Data[i];
                } 
                printf("id is %u\n", temp_id);
                
                switch ( temp_id ) {
                    case 492: {
                         for(i=0;i<temp_len;i++) {
                             y0[i] = temp_data[i];
                         }    
                         break; }
                     case 251: {
                         for(i=0;i<temp_len;i++) {
                             y1[i] = temp_data[i];
                         }    
                         break; }                   
                    
                    case 355: {
                         for(i=0;i<temp_len;i++) {
                             y2[i] = temp_data[i];
                         }    
                         break; }                    
                    
                    case 489: {
                         for(i=0;i<temp_len;i++) {
                             y3[i] = temp_data[i];
                         }    
                         break; }  
              
                    case 201: {
                         for(i=0;i<temp_len;i++) {
                             y4[i] = temp_data[i];
                         }    
                         break; }
                     case 1130: {
                         for(i=0;i<temp_len;i++) {
                             y5[i] = temp_data[i];
                         }    
                         break; }                   
                    
                    case 886: {
                         for(i=0;i<temp_len;i++) {
                             y6[i] = temp_data[i];
                         }    
                         break; }                    
                    
                    case 901: {
                         for(i=0;i<temp_len;i++) {
                             y7[i] = temp_data[i];
                         }    
                         break; }  
                    
                    case 532: {
                         for(i=0;i<temp_len;i++) {
                             y8[i] = temp_data[i];
                         }    
                         break; }
                     case 485: {
                         for(i=0;i<temp_len;i++) {
                             y9[i] = temp_data[i];
                         }    
                         break; }                   
                    
                    case 851: {
                         for(i=0;i<temp_len;i++) {
                             y10[i] = temp_data[i];
                         }    
                         break; }                    
                    
                    case 540: {
                         for(i=0;i<temp_len;i++) {
                             y11[i] = temp_data[i];
                         }    
                         break; }         
                    
                    
                    
                    case 758: {
                         for(i=0;i<temp_len;i++) {
                             y12[i] = temp_data[i];
                         }    
                         break; }
                     case 404: {
                         for(i=0;i<temp_len;i++) {
                             y13[i] = temp_data[i];
                         }    
                         break; }                   
                    
                    case 481: {
                         for(i=0;i<temp_len;i++) {
                             y14[i] = temp_data[i];
                         }    
                         break; }                    
                    
                    case 389: {
                         for(i=0;i<temp_len;i++) {
                             y15[i] = temp_data[i];
                         }    
                         break; }             
                    case 593: {
                         for(i=0;i<temp_len;i++) {
                             y16[i] = temp_data[i];
                         }    
                         break; }                       
                    default:
                        printf("no data\n");
                    
                }
            }
                    
        }
     
    }
     
     
}



#define MDL_UPDATE  /* Change to #undef to remove function */
#if defined(MDL_UPDATE)
  /* Function: mdlUpdate ======================================================
   * Abstract:
   *    This function is called once for every major integration time step.
   *    Discrete states are typically updated here, but this function is useful
   *    for performing any tasks that should only take place once per
   *    integration step.
   */
  static void mdlUpdate(SimStruct *S, int_T tid)
  {
  }
#endif /* MDL_UPDATE */



#define MDL_DERIVATIVES  /* Change to #undef to remove function */
#if defined(MDL_DERIVATIVES)
  /* Function: mdlDerivatives =================================================
   * Abstract:
   *    In this function, you compute the S-function block's derivatives.
   *    The derivatives are placed in the derivative vector, ssGetdX(S).
   */
  static void mdlDerivatives(SimStruct *S)
  {
  }
#endif /* MDL_DERIVATIVES */



/* Function: mdlTerminate =====================================================
 * Abstract:
 *    In this function, you should perform any actions that are necessary
 *    at the termination of a simulation.  For example, if memory was
 *    allocated in mdlStart, this is the place to free it.
 */
static void mdlTerminate(SimStruct *S)
{
    

}


/*=============================*
 * Required S-function trailer *
 *=============================*/

#ifdef  MATLAB_MEX_FILE    /* Is this file being compiled as a MEX-file? */
#include "simulink.c"      /* MEX-file interface mechanism */
#else
#include "cg_sfun.h"       /* Code generation registration function */
#endif
