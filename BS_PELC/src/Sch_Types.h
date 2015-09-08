/*============================================================================*/
/*                        SV C BC SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Include:        %Sch_Types.h%
* Instance:         1
* %version:         1 %
* %created_by:      Michele Balbi %
* %date_created:    July 13 2015 %
*=============================================================================*/
/* DESCRIPTION : Header file for the Scheduler's type definitions.            */
/*============================================================================*/
/* FUNCTION COMMENT :   										              */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 13/07/2015  |                               | Michele Balbi    */
/* First Draft. Added all necessary typedefs.                            	  */
/*============================================================================*/

#ifndef SCH_TYPES_H                               /* To avoid double inclusion */
#define SCH_TYPES_H

/* Includes */
/* -------- */
#include "conti_typedefs.h"

/* Exported types and constants */
/* ---------------------------- */

/* Types definition */
/* typedef */

typedef void (*T_TASK_FUNCTION_PTR)(void);
typedef T_UBYTE T_SCH_TASK_OFFSET;

typedef enum{
	MASK_1p25MS = 1,
	MASK_5MS = 7,
	MASK_10MS = 15,
	MASK_40MS = 63
	/*MASK_25MS = 31,
	MASK_50MS = 63,
	MASK_100MS = 127*/
}E_SCH_TASK_MASK;

typedef enum{
	TASK_BKG,
	TASK_1p25MS,
	TASK_5MS,
	TASK_10MS,
	TASK_40MS
	/*TASK_25MS,
	TASK_50MS,
	TASK_100MS*/
}E_SCH_TASK_ID;

typedef enum{
	TASK_STATE_SUSPENDED,
	TASK_STATE_READY,
	TASK_STATE_RUNNING
}E_SCH_TASK_STATE;

typedef struct {
	E_SCH_TASK_STATE SchTaskState;
	T_TASK_FUNCTION_PTR TaskFunctionControlPtr;
}S_SCH_TASK_CONTROL; /* TaskControl -> TCB (TaskControlBlock)*/

typedef struct {
	T_SCH_TASK_OFFSET SchTaskOffset;
	E_SCH_TASK_MASK SchTaskMask;
	E_SCH_TASK_ID SchTaskId;
	T_TASK_FUNCTION_PTR TaskFunctionPtr;
}S_TASK_DESCRIPTOR;

typedef struct {
	T_UBYTE SchNumberOfTasks;
	const S_TASK_DESCRIPTOR *SchTaskDescriptor;
}S_SCH_CONFIG;

typedef enum{
	SCH_UNINIT,
	SCH_IDLE,
	SCH_INIT,
	SCH_RUNNING,
	SCH_OVERLOAD,
	SCH_HALTED
}E_SCH_STATE;

typedef struct {
	T_UBYTE SchCounter;
	E_SCH_TASK_ID SchTaskRunning;
	E_SCH_STATE SchStatus;
}S_SCH_CONTROL;

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


#endif


