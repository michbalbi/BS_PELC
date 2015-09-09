/*============================================================================*/
/*                        SV C BC SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Include:        %PELC_MessageCtrl.h%
* Instance:         x
* %version:         X %
* %created_by:      Luis Medina %
* %date_created:    2015 %
*=============================================================================*/
/* DESCRIPTION : Header file template                                         */
/*============================================================================*/
/* FUNCTION COMMENT : contains only symbols which are exported to internal    */
/* platform modules. This will not be delivered with the library              */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | DD/MM/YYYY  | SAR/SIF/SCN_xxx               |  Luis Medina     */
/* Integration under Continuus CM                                             */
/*============================================================================*/

#ifndef PELC_MESSAGE_CTRL_H                               /* To avoid double inclusion */
#define PELC_MESSAGE_CTRL_H

/* Includes */
#include "conti_typedefs.h"
/* -------- */


/* Exported types and constants */
/* ---------------------------- */

/* Types definition */
typedef enum {
	E_MSG_IDLE,
	E_MSG_RECEIVED
}CAN_MESSAGE_HANDLER_STATE;


extern CAN_MESSAGE_HANDLER_STATE re_CANMsgHandlerState;
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
	extern void PELC_CmdMsgProcess (void);
	extern void PELC_MsgSendStatus (T_UBYTE lub_DoorStat,T_UBYTE lub_HighB_Stat, T_UBYTE lub_BrakeStat);

/* Functions macros */


/* Exported defines */

#define STOP_CMD 			0x01
#define TURN_CMD 			0x03
#define HAZARD_CMD 			0x04
#define MAIN_LIGHT_CMD 		0x05

#define ACTIVE_LIGHTS		0x0F
#define INACTIVE_LIGHTS		0x00
#define TURN_OFF 			0x01
#define TURN_RIGHT 			0x0A
#define TURN_LEFT 			0x0B

#define MAINL_OFF			0x01
#define MAINL_DAY			0x02
#define MAINL_FULL			0x03
#define MAINL_AUTO			0x04

#endif