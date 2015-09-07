/*============================================================================*/
/*                        SV C BC SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Include:        %MPC5606B_ADC_lib.h%
* Instance:         1
* %version:         1 %
* %created_by:      Michele Balbi %
* %date_created:    July 8 2015 %
*=============================================================================*/
/* DESCRIPTION : Header file for ADC functions.		      					  */
/*============================================================================*/
/* FUNCTION COMMENT :   Contains prototypes for ADC functions.         		  */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 08/07/2015  |                               | Michele Balbi    */
/* First Draft 																  */
/*============================================================================*/

#ifndef MCP5606B_ADC_LIB
#define MCP5606B_ADC_LIB

/* Includes */
/* -------- */
#include "MPC5606B.h"
#include "MPC5606B_GPIO_lib.h"

/* Exported types and constants */
/* ---------------------------- */

/* Types definition */
/* typedef */


/*==================================================*/ 
/* Declaration of exported constants                */
/*==================================================*/ 
/* BYTE constants */


/* WORD constants */


/* LONG and STRUCTURE constants */



/*======================================================*/ 
/* Definition of RAM variables                          */
/*======================================================*/ 
/* BYTES */


/* WORDS */


/* LONGS and STRUCTURES */


/*======================================================*/ 
/* close variable declaration sections                  */
/*======================================================*/ 

/* Exported functions prototypes and macros */
/* ---------------------------------------- */

/* Functions prototypes */

/* Functions macros */


/* Exported defines */
#define ADC_0_CHANNEL0 				0
#define ADC_0_CHANNEL1 				1
#define ADC_0_CHANNEL2 				2
#define ADC_0_CHANNEL3 				3

#define ADC_0_ONESHOTMODE() 		(ADC_0.MCR.B.MODE = 0)
#define ADC_0_SCANMODE() 			(ADC_0.MCR.B.MODE = 1)
#define ADC_0_TURNON() 				(ADC_0.MCR.B.PWDN = 0)
#define ADC_0_TURNOFF() 			(ADC_0.MCR.B.PWDN = 1)
#define ADC_0_STARTCONVERSION()		(ADC_0.MCR.B.NSTART = 1)
#define ADC_0_STOPCONVERSION()		(ADC_0.MCR.B.NSTART = 0)
#define ADC_0_GETDATA(channel)		(ADC_0.CDR[##channel].B.CDATA)
#define ADC_0_ISDATAVALID(channel) 	(ADC_0.CDR[##channel].B.VALID)

#endif