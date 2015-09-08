/*============================================================================*/
/*                        SV C CE SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:         %MPC5606B_INTERRUPTS_lib.c%
* Instance:         1
* %version:         1 %
* %created_by:      Michele Balbi %
* %date_created:    August 5 2015 %
*=============================================================================*/
/* DESCRIPTION : C source code for Interrupts configuration.                  */
/*============================================================================*/
/* FUNCTION COMMENT : This file describes the C source code used to initialize*/
/* the interrupts used in the application.                                    */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 17/07/2015  |                               | Michele Balbi    */
/* 	Added Ints_Init() function.                                               */
/*============================================================================*/

/* Includes */
/* -------- */
#include "MPC5606B_INTERRUPTS_lib.h"
#include "Sch.h"

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
void Ints_InstallIntHandler(INTCInterruptFn lp_handler, T_UWORD lub_vector, T_UBYTE lub_priority);


/* Exported functions prototypes */
/* ----------------------------- */

/* Inline functions */
/* ---------------- */


/* Private functions */
/* ----------------- */
 /********************************************************************************
 *  Name                 :	Ints_Init
 *  Description          :	Interrupts configuration function.
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation :  This routine configures the interrupts used in the 
 							application.
 ********************************************************************************/
 void Ints_InstallIntHandler(INTCInterruptFn lp_handler, T_UWORD lub_vector, T_UBYTE lub_priority) {
	INTC_InstallINTCInterruptHandler(lp_handler, lub_vector, lub_priority);
 }

/* Exported functions */
/* ------------------ */
/********************************************************************************
 *  Name                 :	Ints_Init
 *  Description          :	Interrupts configuration function.
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation :  This routine configures the interrupts used in the 
 							application.
 ********************************************************************************/
 void Ints_Init(void){	
	
	INT_SW_VECTOR_MODE();
	
	Ints_InstallIntHandler(&Sch_OSTick, PIT0_Vector, PRIORITY13);
	
	INTC_InitINTCInterrupts();
 	INT_ENABLE_INTS();
 }

 