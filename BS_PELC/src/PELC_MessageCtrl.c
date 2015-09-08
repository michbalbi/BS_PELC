/*============================================================================*/
/*                        SV C CE SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:         %PELC_MessageCtrl.c%
* Instance:         x
* %version:         x %
* %created_by:      Luis Medina %
* %date_created:     2015 %
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
/*  1.0      | DD/MM/YYYY  |                               | Luis Medina      */
/* Integration under Continuus CM                                             */
/*============================================================================*/

/* Includes */
	#include "PELC_MessageCtrl.h"
	#include "typedefs.h"
	#include "Can_Manager.h"
	#include "PELC_LightsControl.h"
/* -------- */


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

CAN_PduType    pdu_status_lights;
T_UBYTE can_response[3]={0,0,0};

/* WORD RAM variables */


/* LONG and STRUCTURE RAM variables */
CAN_MESSAGE_HANDLER_STATE re_CANMsgHandlerState = E_MSG_IDLE;

/*CAN_PduType pdu_handler_ECU;*/

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
/**************************************************************
 *  Name                 : inline_func	2
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/


/* Private functions */
/* ----------------- */
/**************************************************************
 *  Name                 : private_func
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/


/* Exported functions */
/* ------------------ */
/**************************************************************
 *  Name                 :	Commads_Message_Process
 *  Description          :	It sets Lights' functions State Machines.
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/

void PELC_CmdMsgProcess(void){
	
	T_UBYTE lub_CommandID = 0;
	T_UBYTE lub_NumOfParamtrs = 0;
	T_UBYTE laub_Data[3] = {0,0,0};
	T_UBYTE lub_CheckSumRec = CanMessage_PduHandler0.msg_data_field[5];
	T_UBYTE lub_i;
	T_UBYTE lub_ChSumExpctd;
	
	for(lub_i=0;lub_i<lub_NumOfParamtrs;lub_i++){
			laub_Data[lub_i] = CanMessage_PduHandler0.msg_data_field[lub_i+2];
	}
	
	lub_ChSumExpctd = laub_Data[0]^laub_Data[1]^laub_Data[2];
	
	if((re_CANMsgHandlerState == E_MSG_RECEIVED) && (lub_CheckSumRec == lub_ChSumExpctd)){
	
		lub_CommandID = CanMessage_PduHandler0.msg_data_field[0];
		lub_NumOfParamtrs = CanMessage_PduHandler0.msg_data_field[1];
		
		switch(lub_CommandID){
			case STOP_CMD: 
					if(laub_Data[0] == ACTIVE_LIGHTS){
						re_StopCmdState = E_STOP_ACTIVE;
					}
					else if(laub_Data[0] == INACTIVE_LIGHTS){
						re_StopCmdState = E_STOP_INACTIVE;
					}
				break;
			
			case TURN_CMD:
					switch(laub_Data[0]){
						case TURN_OFF: re_TurnCmdState = E_TURN_INACTIVE;
							break;
							
						case TURN_RIGHT: re_TurnCmdState = E_TURN_ACTIVE_ON_RIGHT;
								/*VARIABLE_MULTIPLO_ON = laub_Data[1] */
					 			/*VARIABLE_MULTIPLO_OFF = laub_Data[2] */
							break;
							
						case TURN_LEFT: re_TurnCmdState = E_TURN_ACTIVE_ON_LEFT;
								/*VARIABLE_MULTIPLO_ON = laub_Data[1] */
					 			/*VARIABLE_MULTIPLO_OFF = laub_Data[2] */
							break;
							
						default:
							break;
					
					} /*END switch DATA*/
				break;
					
				
			case HAZARD_CMD:
					if(laub_Data[0] == INACTIVE_LIGHTS){
						re_HazardCmdState = E_HAZARD_INACTIVE;
					}
					else if(laub_Data[0] == ACTIVE_LIGHTS){
						re_HazardCmdState = E_HAZARD_ACTIVE_ON;
						/*VARIABLE_MULTIPLO_ON = laub_Data[1] */
						/*VARIABLE_MULTIPLO_OFF = laub_Data[2] */
					}
				break;
				
			case MAIN_LIGHT_CMD:
					switch(laub_Data[0]){
						case MAINL_OFF: re_MainLightsCmdState = E_OFF;
							break;
							
						case MAINL_DAY: re_MainLightsCmdState = E_DAY;
							break;
							
						case MAINL_FULL: re_MainLightsCmdState = E_FULL;
							break;
							
						case MAINL_AUTO: re_MainLightsCmdState = E_AUTO;
							break;
							
						default:
							break;
					} /*End MAIN_LIGHT_CMD*/
				break;
				
			default: /*Do nothing*/
				break;
		}	/*END switch COMMAND ID*/
		
	re_CANMsgHandlerState = E_MSG_IDLE;
		
	} 	/*END IF msg received*/
}



/**************************************************************
 *  Name                 :	PELC_MsgSendStatus
 *  Description          :	Send status of breack lights, High Beams and Door.
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/
 
 void PELC_MsgSendStatus (T_UBYTE lub_DoorStat,T_UBYTE lub_HighB_Stat, T_UBYTE lub_BrakeStat){
 	
 	can_response[0] = lub_DoorStat;
	can_response[1] = lub_HighB_Stat;
	can_response[2] = lub_BrakeStat;
 	
 	pdu_status_lights.can_mb_nr = 2;
	pdu_status_lights.can_dlc = 3;
	pdu_status_lights.can_sdu = can_response;
 	
 	CAN_SendFrame(pdu_status_lights);
 }