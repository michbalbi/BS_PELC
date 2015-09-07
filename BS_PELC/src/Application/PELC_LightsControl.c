/*============================================================================*/
/*                        SV C CE SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:         %PELC_LightsControl.c%
* Instance:         x
* %version:         x %
* %created_by:      Michele Balbi %
* %date_created:    2015 %
*=============================================================================*/
/* DESCRIPTION : C source template file                                       */
/*============================================================================*/
/* FUNCTION COMMENT : This file describes the C source template according to  */
/* the new software platform                                                  */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | DD/MM/2015  |                               | Michele Balbi    */
/* 								                                              */
/*============================================================================*/

/* Includes */
/* -------- */
#include "PELC_LightsControl.h"
#include "MPC5606B_GPIO_lib.h"
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
MAIN_LIGHTS_CMD_STATE re_MainLightsCmdState = E_OFF;
TURN_CMD_STATE re_TurnCmdState = E_TURN_INACTIVE;
HAZARD_CMD_STATE re_HazardCmdState = E_HAZARD_INACTIVE;
STOP_CMD_STATE re_StopCmdState = E_STOP_INACTIVE;

/*extern CAN_MESSAGE_HANDLER_STATE re_CANMsgHandlerState;*/
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
void PELC_TurnOnFull(T_UBYTE lub_pcr){
	GPIO_AS_OUTPUT(lub_pcr);
	OUTPUT_HIGH(lub_pcr);
}

/**************************************************************
 *  Name                 :	export_func
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/
void PELC_TurnOff(T_UBYTE lub_pcr){
	GPIO_AS_OUTPUT(lub_pcr);
	OUTPUT_LOW(lub_pcr);
}

/**************************************************************
 *  Name                 :	export_func
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/
void PELC_TurnOnLevel(T_UBYTE lub_pcr, T_UBYTE lub_Channel, T_UBYTE lub_DutyCycle, T_UBYTE lub_Freq){
	GPIO_ALT_MODE_1(lub_pcr);
	PWM_Channel_Set(lub_Channel, lub_DutyCycle, lub_Freq);
}


/*
Sch Tasks are 1.25, 5, 10 and 40MS
*/
void PELC_Task_1P25MS(void){
	
}

void PELC_Task_5MS(void){
	/*if(re_CANMsgHandlerState == E_MSG_RECEIVED){
		PELC_ProcessCANMsg();
	}*/
}

void PELC_LightSwitch_100MS(void){
	/*if(){
		
	}*/
}

void PELC_SendStatus_100MS(void){
	
}

void PELC_Task_500MS(void){
	
}