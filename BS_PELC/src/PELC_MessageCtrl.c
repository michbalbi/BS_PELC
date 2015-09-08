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
 *  Name                 :	export_func
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/

void ECU_Process_Message(void){
	
	T_UBYTE lub_CommandID = 0;
	T_UBYTE lub_NumOfParameters = 0;
	T_UBYTE laub_Data[3] = {0,0,0};
	T_UBYTE lub_CheckSum = 0;
	T_UBYTE lub_i;
	
	if(re_CANMsgHandlerState == E_MSG_RECEIVED){
	
		lub_CommandID = CanMessage_PduHandler0.msg_data_field[0];
		lub_NumOfParameters = CanMessage_PduHandler0.msg_data_field[1];
		lub_CheckSum = CanMessage_PduHandler0.msg_data_field[5];
		
		for(lub_i=0;lub_i<3;lub_i++){
			laub_Data[lub_i] = CanMessage_PduHandler0.msg_data_field[lub_i+2];
		}
		
		switch(lub_CommandID){
			case STOP_CMD:
				break;
			
			case TURN_CMD:
				break;
				
			case HAZARD_CMD:
				break;
				
			case MAIN_LIGHT_CMD:
				break;
				
			default:
				break;
		}
	}
}