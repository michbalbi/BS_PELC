/*============================================================================*/
/*                        SV C CE SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:         %MPC5606B_PWM_lib.c%
* Instance:         1
* %version:         1 %
* %created_by:      Michele Balbi %
* %date_created:    August 31 2015 %
*=============================================================================*/
/* DESCRIPTION : C source file for PWM functionality.                         */
/*============================================================================*/
/* FUNCTION COMMENT : This file describes the C source file used to configure */
/* the PWM functionality through the OPWMFB mode in the EMIOS module.         */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 31/08/2015  |                               | Michele Balbi    */
/* 	First draft.    			                                              */
/*============================================================================*/

/* Includes */
/* -------- */
#include "MPC5606B_PWM_lib.h"

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
void PWM_Disable(void){
	EMIOS_0.MCR.B.FRZ = 1; 			/* Enable channel freezing */
	EMIOS_0.MCR.B.GTBE = 0;			/* Global Time Base Disable  */
	EMIOS_0.MCR.B.GPREN = 0;		/* 1. Global Prescaler Disabled */
}

void PWM_Enable(T_UBYTE lub_GlobalPrescaler){
	EMIOS_0.MCR.B.GPRE = lub_GlobalPrescaler;		/* Global Prescaler */
	
	/* Now, enable everything back*/
	EMIOS_0.MCR.B.GPREN = 1;
	EMIOS_0.MCR.B.GTBE = 1;
	
}

void PWM_Channel_Init(T_UBYTE lub_Channel, T_UBYTE lub_ChPrescaler, T_UBYTE lub_DutyCycle, T_UBYTE lub_Freq){
	EMIOS_0.CH[lub_Channel].CCR.B.MODE = 1;						/* GPIO output mode for CH[x] */
	EMIOS_0.CH[lub_Channel].CCR.B.FREN = 1; 					/* CH[x] is now frozen */
	
	/* Steps using Reference Manual guide */
	EMIOS_0.CH[lub_Channel].CCR.B.UCPEN = 0;					/* 2. Channel Prescaler Disabled */
	
	EMIOS_0.CH[lub_Channel].CCR.B.BSL = 0x3; 					/*    Bus Selection to internal counter for CH[0] */
	EMIOS_0.CH[lub_Channel].CCNTR.R = 2; 						/* 3. Internal Counter initial value */
	EMIOS_0.CH[lub_Channel].CCR.B.UCPRE = lub_ChPrescaler - 1u;	/*    Channel prescaler set to 4 */
	EMIOS_0.CH[lub_Channel].CADR.R = lub_DutyCycle;				/* 4. Set A register */
	EMIOS_0.CH[lub_Channel].CBDR.R = lub_Freq;					/* 4. Set B register */
	
	EMIOS_0.CH[lub_Channel].CCR.B.FREN = 0;
	
	EMIOS_0.CH[lub_Channel].CCR.B.UCPEN = 1;
	
	EMIOS_0.CH[lub_Channel].CCR.B.MODE = 0x58; 	/* OPWFMB mode, 0101 1000 */
	
}
