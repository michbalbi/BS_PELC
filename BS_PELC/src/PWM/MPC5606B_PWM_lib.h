/*============================================================================*/
/*                        SV C BC SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Include:        %MPC5606B_PWM_lib.h%
* Instance:         1
* %version:         1 %
* %created_by:      Michele Balbi %
* %date_created:    August 31 2015 %
*=============================================================================*/
/* DESCRIPTION : Header file for PWM functionality.                           */
/*============================================================================*/
/* FUNCTION COMMENT :   										              */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 31/08/2015  |                               | Michele Balbi    */
/* First Draft.  															  */
/*============================================================================*/

#ifndef MPC5606B_PWM_LIB_H              /* To avoid double inclusion */
#define MPC5606B_PWM_LIB_H

/* Includes */
/* -------- */
#include "MPC5606B.h"
#include "conti_typedefs.h"
/*#include "MPC5606B_GPIO_lib.h"*/

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
extern void PWM_Channel_Init(T_UBYTE lub_Channel, T_UBYTE lub_ChPrescaler, T_UBYTE lub_DutyCycle, T_UBYTE lub_Freq);
extern void PWM_Channel_Set(T_UBYTE lub_Channel, T_UBYTE lub_DutyCycle, T_UBYTE lub_Freq);
extern void PWM_Enable(T_UBYTE lub_GlobalPrescaler);
extern void PWM_Disable(void);

/* Functions macros */


/* Exported defines */
#define EMIOS_0_CH0  0
#define EMIOS_0_CH1  1
#define EMIOS_0_CH2  2
#define EMIOS_0_CH3  3
#define EMIOS_0_CH4  4
#define EMIOS_0_CH5  5
#define EMIOS_0_CH6  6
#define EMIOS_0_CH7  7
#define EMIOS_0_CH8  8
#define EMIOS_0_CH16 16
#define EMIOS_0_CH23 23
#define EMIOS_0_CH24 24

#define EMIOS_0_CH0_PCR  0
#define EMIOS_0_CH1_PCR  1
#define EMIOS_0_CH2_PCR  2
#define EMIOS_0_CH3_PCR  3
#define EMIOS_0_CH4_PCR  4
#define EMIOS_0_CH5_PCR  5
#define EMIOS_0_CH6_PCR  6
#define EMIOS_0_CH7_PCR  7
#define EMIOS_0_CH8_PCR  8
#define EMIOS_0_CH16_PCR 64
#define EMIOS_0_CH23_PCR 71
#define EMIOS_0_CH24_PCR 75

/*#define EMIOS_0_GLOBAL_PRESCALER 255u
#define EMIOS_0_FREQ			 62500u
#define EMIOS_0_CH_PRESCALER	 (MCU_FREQ/((EMIOS_0_GLOBAL_PRESCALER+1)*EMIOS_0_FREQ))
#define PWM_FREQ 	 			 1000u
#define PWM_B_REG				 (EMIOS_0_FREQ/PWM_FREQ)
#define PWM_DUTY_CYCLE			 50u
#define PWM_A_REG				 ((PWM_DUTY_CYCLE/100)*PWM_B_REG)*/

#endif


