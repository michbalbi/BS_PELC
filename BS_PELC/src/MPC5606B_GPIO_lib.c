/*============================================================================*/
/*                        SV C CE SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:         %MPC5606B_GPIO_lib.c%
* Instance:         1
* %version:         1 %
* %created_by:      Michele Balbi %
* %date_created:    July 17 2015 %
*=============================================================================*/
/* DESCRIPTION : C source code for GPIO configuration.                        */
/*============================================================================*/
/* FUNCTION COMMENT : This file describes the C source code used to initialize*/
/* the GPIO pins.                                                             */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 17/07/2015  |                               | Michele Balbi    */
/* 	Added GPIO_Init() function.                                               */
/*============================================================================*/

/* Includes */
/* -------- */
#include "MPC5606B_GPIO_lib.h"

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
/********************************************************************************
 *  Name                 :	GPIO_Init
 *  Description          :	GPIO configuration function.
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation :  This routine configures the GPIOs used in the 
 							application.
 ********************************************************************************/
 void GPIO_Init(void){
 
 	GPIO_AS_OUTPUT(LED1);
	GPIO_AS_OUTPUT(LED2);
	GPIO_AS_OUTPUT(LED3);
	GPIO_AS_OUTPUT(LED4);
	
	LED_OFF(LED1);
	LED_OFF(LED2);
	LED_OFF(LED3);
	LED_OFF(LED4);

	
 }