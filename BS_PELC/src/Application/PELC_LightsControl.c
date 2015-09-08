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
#include "PELC_MessageCtrl.h"

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
HW_CONFIG re_HWConfig = E_STD;
MAIN_LIGHTS_CMD_STATE re_MainLightsCmdState = E_OFF;
TURN_CMD_STATE re_TurnCmdState = E_TURN_INACTIVE;
HAZARD_CMD_STATE re_HazardCmdState = E_HAZARD_INACTIVE;
STOP_CMD_STATE re_StopCmdState = E_STOP_INACTIVE;

T_UWORD ruw_LightLevel = 0;
T_UWORD ruw_LightLevelPrev = 0;
/*extern CAN_MESSAGE_HANDLER_STATE re_CANMsgHandlerState;*/
/*======================================================*/ 
/* close variable declaration sections                  */
/*======================================================*/ 

/* Private defines */

#define LIGHT_NIGHT_THR 307u
#define LIGHT_AFT_THR 	614u
#define LIGHT_DAWN_THR 	338
#define LIGHT_DAY_THR 	644u
#define LIGHT_MAX_THR	1023u
#define LIGHT_MIN_THR	0u

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

/**************************************************************
 *  Name                 :	export_func
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/
void PELC_SetLights(MAIN_LIGHTS_CMD_STATE le_CmdState){
	
	switch(le_CmdState){
	
		case E_OFF: 
			PELC_TurnOff(PARKL_FL_PCR);
			PELC_TurnOff(PARKL_FR_PCR);
			PELC_TurnOff(BLINKERL_FL_PCR);
			PELC_TurnOff(BLINKERL_FR_PCR);
			PELC_TurnOff(HEADL_FL_PCR);
			PELC_TurnOff(HEADL_FR_PCR);
			PELC_TurnOff(PARKL_RL_PCR);
			PELC_TurnOff(PARKL_RR_PCR);
			PELC_TurnOff(STOPL_RL_PCR);
			PELC_TurnOff(STOPL_RR_PCR);
			break;
		
		case E_DAY:
			switch(re_HWConfig){
				case E_STD:
					PELC_TurnOnLevel(PARKL_FL_PCR, PARKL_FL_PWMCH, 20, 63);
					PELC_TurnOnLevel(PARKL_FR_PCR, PARKL_FR_PWMCH, 20, 63);
					PELC_TurnOnLevel(BLINKERL_FL_PCR, BLINKERL_FL_PWMCH, 20, 63);
					PELC_TurnOnLevel(BLINKERL_FR_PCR, BLINKERL_FR_PWMCH, 20, 63);
					PELC_TurnOff(HEADL_FL_PCR);
					PELC_TurnOff(HEADL_FR_PCR);
					PELC_TurnOnLevel(PARKL_RL_PCR, PARKL_RL_PWMCH, 20, 63);
					PELC_TurnOnLevel(PARKL_RR_PCR, PARKL_RR_PWMCH, 20, 63);
					PELC_TurnOnLevel(STOPL_RL_PCR, STOPL_RL_PWMCH, 20, 63);
					PELC_TurnOnLevel(STOPL_RR_PCR, STOPL_RR_PWMCH, 20, 63);
					break;
				
				case E_HIGH: 
					PELC_TurnOnFull(PARKL_FL_PCR);
					PELC_TurnOnFull(PARKL_FR_PCR);
					PELC_TurnOff(HEADL_FL_PCR);
					PELC_TurnOff(HEADL_FR_PCR);
					PELC_TurnOnFull(PARKL_RL_PCR);
					PELC_TurnOnFull(PARKL_RR_PCR);
					break;
					
				case E_LUX: 
					PELC_TurnOnFull(PARKL_FL_PCR);
					PELC_TurnOnFull(PARKL_FR_PCR);
					PELC_TurnOff(HEADL_FL_PCR);
					PELC_TurnOff(HEADL_FR_PCR);
					PELC_TurnOnFull(PARKL_RL_PCR);
					PELC_TurnOnFull(PARKL_RR_PCR);
					break;
				
				default:
					break;
			}
			break;
			
		case E_FULL:
			switch(re_HWConfig){
				case E_STD:
					PELC_TurnOnLevel(PARKL_FL_PCR, PARKL_FL_PWMCH, 20, 63);
					PELC_TurnOnLevel(PARKL_FR_PCR, PARKL_FR_PWMCH, 20, 63);
					PELC_TurnOnLevel(BLINKERL_FL_PCR, BLINKERL_FL_PWMCH, 20, 63);
					PELC_TurnOnLevel(BLINKERL_FR_PCR, BLINKERL_FR_PWMCH, 20, 63);
					PELC_TurnOnFull(HEADL_FL_PCR);
					PELC_TurnOnFull(HEADL_FR_PCR);
					PELC_TurnOnLevel(PARKL_RL_PCR, PARKL_RL_PWMCH, 20, 63);
					PELC_TurnOnLevel(PARKL_RR_PCR, PARKL_RR_PWMCH, 20, 63);
					PELC_TurnOnLevel(STOPL_RL_PCR, STOPL_RL_PWMCH, 20, 63);
					PELC_TurnOnLevel(STOPL_RR_PCR, STOPL_RR_PWMCH, 20, 63);
					break;
				
				case E_HIGH: 
					PELC_TurnOnFull(PARKL_FL_PCR);
					PELC_TurnOnFull(PARKL_FR_PCR);
					PELC_TurnOnFull(HEADL_FL_PCR);
					PELC_TurnOnFull(HEADL_FR_PCR);
					PELC_TurnOnFull(PARKL_RL_PCR);
					PELC_TurnOnFull(PARKL_RR_PCR);
					break;
					
				case E_LUX: 
					PELC_TurnOnFull(PARKL_FL_PCR);
					PELC_TurnOnFull(PARKL_FR_PCR);
					PELC_TurnOnFull(HEADL_FL_PCR);
					PELC_TurnOnFull(HEADL_FR_PCR);
					PELC_TurnOnFull(PARKL_RL_PCR);
					PELC_TurnOnFull(PARKL_RR_PCR);
					break;
			}
			break;
		
		default:
			break;
	}
}

/*
Sch Tasks are 1.25, 5, 10 and 40MS
*/
void PELC_Task_1P25MS(void){
	
}

void PELC_ChkMsg_5MS(void){
	/*if(re_CANMsgHandlerState == E_MSG_RECEIVED){
		PELC_CmdMsgProcess();
	}*/
}

void PELC_LightSwitch_100MS(void){
	
	switch(re_MainLightsCmdState){
		
		case E_OFF:
			PELC_SetLights(E_OFF);
			break;
		
		case E_DAY:
			PELC_SetLights(E_DAY);
			break;
			
		case E_FULL:
			PELC_SetLights(E_FULL);
			break;
			
		case E_AUTO:
			if(ruw_LightLevel < ruw_LightLevelPrev){
				if(ruw_LightLevel>=LIGHT_MIN_THR && ruw_LightLevel<LIGHT_NIGHT_THR){
					PELC_SetLights(E_FULL);
				}
				
				if(ruw_LightLevel>=LIGHT_NIGHT_THR && ruw_LightLevel<LIGHT_AFT_THR){
					PELC_SetLights(E_DAY);
				}
				
				if(ruw_LightLevel>=LIGHT_AFT_THR && ruw_LightLevel<=LIGHT_MAX_THR){
					PELC_SetLights(E_OFF);
				}
			} else if(ruw_LightLevel >= ruw_LightLevelPrev){
				if(ruw_LightLevel>=LIGHT_MIN_THR && ruw_LightLevel<LIGHT_DAWN_THR){
					PELC_SetLights(E_FULL);
				}
				
				if(ruw_LightLevel>=LIGHT_DAWN_THR && ruw_LightLevel<LIGHT_DAY_THR){
					PELC_SetLights(E_DAY);
				}
				
				if(ruw_LightLevel>=LIGHT_DAY_THR && ruw_LightLevel<=LIGHT_MAX_THR){
					PELC_SetLights(E_OFF);
				}
			}
			break;
		
		default:
			break;
	}
}

void PELC_SendStatus_100MS(void){
	/*PELC_MsgSendStatus();*/
}

void PELC_GetLightLevel_500MS(void){
	
	ruw_LightLevelPrev = ruw_LightLevel;
	ruw_LightLevel = (T_UWORD)LightMeter_GetLightLevel();
	
}