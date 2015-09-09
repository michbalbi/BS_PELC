/*============================================================================*/
/*                        SV C BC SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Include:        %PELC_LightsControl.h%
* Instance:         x
* %version:         x.x %
* %created_by:      Michele Balbi %
* %date_created:    2015 %
*=============================================================================*/
/* DESCRIPTION : Header file for 				                              */
/*============================================================================*/
/* FUNCTION COMMENT :   										              */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | DD/MM/2015  |                               | Michele Balbi    */
/* First Draft 																  */
/*============================================================================*/

#ifndef PELC_LIGHTS_CTRL_H                               /* To avoid double inclusion */
#define PELC_LIGHTS_CTRL_H

/* Includes */
/* -------- */


/* Exported types and constants */
/* ---------------------------- */

/* Types definition */
/* typedef */

typedef enum {
	E_STD,
	E_HIGH,
	E_LUX
}HW_CONFIG;

typedef enum {
	E_OFF,
	E_DAY,
	E_FULL,
	E_AUTO
}MAIN_LIGHTS_CMD_STATE;

typedef enum {
	E_TURN_INACTIVE,
	E_TURN_ACTIVE_ON,
	E_TURN_ACTIVE_OFF,
	E_TURN_ACTIVE_ON_RIGHT,
	E_TURN_ACTIVE_OFF_RIGHT,
	E_TURN_ACTIVE_ON_LEFT,
	E_TURN_ACTIVE_OFF_LEFT
}TURN_CMD_STATE;

typedef enum{
	E_TURN_RIGHT,
	E_TURN_LEFT
}TURN_CMD_SIDE;

typedef enum {
	E_HAZARD_INACTIVE,
	E_HAZARD_ACTIVE_ON,
	E_HAZARD_ACTIVE_OFF
}HAZARD_CMD_STATE;

typedef enum {
	E_STOP_INACTIVE,
	E_STOP_ACTIVE
}STOP_CMD_STATE;


extern MAIN_LIGHTS_CMD_STATE re_MainLightsCmdState;
extern TURN_CMD_STATE re_TurnCmdState;
extern TURN_CMD_SIDE re_TurnCmdSide;
extern HAZARD_CMD_STATE re_HazardCmdState;
extern STOP_CMD_STATE re_StopCmdState; 
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

#define PARKL_FL_PWMCH		0
#define BLINKERL_FL_PWMCH	1
#define PARKL_FR_PWMCH		2
#define BLINKERL_FR_PWMCH	3
#define PARKL_RL_PWMCH		4
#define STOPL_RL_PWMCH		5
#define PARKL_RR_PWMCH		6
#define STOPL_RR_PWMCH		7

#define PARKL_FL_PCR		0
#define BLINKERL_FL_PCR		1
#define PARKL_FR_PCR		2
#define BLINKERL_FR_PCR		3
#define PARKL_RL_PCR		4
#define STOPL_RL_PCR		5
#define PARKL_RR_PCR		6
#define STOPL_RR_PCR		7

#define HEADL_FL_PCR		34
#define HEADL_FR_PCR		35
#define BLINKERL_RL1_PCR	36
#define BLINKERL_RL2_PCR	37
#define BLINKERL_RL3_PCR	38
#define BLINKERL_RR1_PCR	39
#define BLINKERL_RR2_PCR	40
#define BLINKERL_RR3_PCR	41

#endif


