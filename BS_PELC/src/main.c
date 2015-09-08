/*============================================================================*/
/*                        SV C CE SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:         %main.c%
* Instance:         1
* %version:         1 %
* %created_by:      Michele Balbi %
* %date_created:    July 13 2015 %
*=============================================================================*/
/* DESCRIPTION : C source template file for the PELC application module.      */
/*============================================================================*/
/* FUNCTION COMMENT : This file describes the C source code which prepares    */
/* the environment for the execution of the PELC module.                      */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | DD/MM/2015  |                               | Michele Balbi    */
/* 	First draft of the file. Includes used libraries.                         */
/*============================================================================*/

/* Includes */
/* -------- */
#include "MPC5606B.h"
#include "conti_typedefs.h"
#include "MPC5606B_GPIO_lib.h"
#include "MPC5606B_ClkInit.h"
#include "MPC5606B_INTERRUPTS_lib.h"
#include "MPC5606B_PIT_lib.h"
#include "MemAlloc_Cfg.h"
#include "Can.h"
#include "Can_Cfg.h"
#include "bspi.h"
#include "Sch.h"

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



/* ---------------- MAIN FUNCTION -------------------------- */
/**************************************************************
 *  Name                 :	main
 *  Description          :
 *  Parameters           :	void
 *  Return               :	void
 *  Critical/explanation :  The main routine initializes the
 							components used in this system.
 **************************************************************/
int main(void) {
	
	initModesAndClock();    /* Initialize mode entries and system clock */
	disableWatchdog();      /* Disable watchdog */
	initPeriClkGen();       /* Initialize peripheral clock generation for DSPIs */
	
	MemAllocInit(&MemAllocConfig);
	
	/* SBC dependencies */
	InitDSPI_1();
	ConfigureMZC33905DSPI_1();
	
	/* CAN Initialization */
	CAN_Initialization(&can_driver_config);
	
    Sch_Init(&cs_SchConfig);
    Ints_Init();
    GPIO_Init();
    
    Sch_Start(); 
	
	while(1) {
		; 
	} /* Execution shall never reach this for*/
	
	return 0;
}

