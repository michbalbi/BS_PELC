/*============================================================================*/
/*                        SV C CE SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:         %MPC5606B_ADC_lib.c%
* Instance:         1
* %version:         1 %
* %created_by:      Michele Balbi %
* %date_created:    July 8 2015 %
*=============================================================================*/
/* DESCRIPTION : C source file to implement ADC functions.                    */
/*============================================================================*/
/* FUNCTION COMMENT : This C file contains the functions needed to use the    */
/* MCU's ADC module.                                                          */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 08/07/2015  |                               | Michele Balbi    */
/* 								                                              */
/*============================================================================*/

/* Includes */
/* -------- */
#include "MPC5606B_ADC_lib.h"

/* Functions macros, constants, types and datas         */
/* ---------------------------------------------------- */
/* Functions macros */

/*==================================================*/ 
/* Definition of constants                          */
/*==================================================*/ 
/* BYTE constants */


/* WORD constants */


/* LONG and STRUCTURE constants */



/*======================================================*/ 
/* Definition of RAM variables                          */
/*======================================================*/ 
/* BYTE RAM variables */


/* WORD RAM variables */


/* LONG and STRUCTURE RAM variables */


/*======================================================*/ 
/* close variable declaration sections                  */
/*======================================================*/ 

/* Private defines */


/* Private functions prototypes */
/* ---------------------------- */



/* Exported functions prototypes */
/* ----------------------------- */

/* Inline functions */
/* ---------------- */


/* Private functions */
/* ----------------- */



/* Exported functions */
/* ------------------ */
/**************************************************************
 *  Name                 :	export_func
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/
void ADC_0_Init(void){
	ADC_0_SCANMODE();  		/* Initialize ADC0 in one-shot mode, still power-down */
	ADC_0.NCMR0.B.CH2 = 1; 		/* Enable CH2 */
	ADC_0.CTR0.R = 0x00008411;  /* Conversion times for 32MHz ADClock. From datasheet */
	ADC_0.DSDR.R = 2; 			/* Decode Signals D Register, 1 ADC clock cycle delay */
	ADC_0.PDEDR.R = 1; 			/* Power-down exit delay */
	ADC_0_TURNON(); 			/* Exit Power-down mode */
}
