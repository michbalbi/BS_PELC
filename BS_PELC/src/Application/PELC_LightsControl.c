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

TURN_CMD_STATE re_TurnCmdState = E_TURN_CMD_INACTIVE;
TURNL_STATE re_TurnLState = E_TURNL_INACTIVE;
TURN_CMD_SIDE re_TurnCmdSide = E_TURN_RIGHT;

HAZARD_CMD_STATE re_HazardCmdState = E_HAZARD_CMD_INACTIVE;
HAZARDL_STATE re_HazardLState = E_HAZARDL_INACTIVE;

STOP_CMD_STATE re_StopCmdState = E_STOP_INACTIVE;

T_UWORD ruw_LightLevel = 0;
T_UWORD ruw_LightLevelPrev = 0;
T_UWORD ruw_TurnCmdOnTime = 0;
T_UWORD ruw_TurnCmdOffTime = 0;
T_UWORD ruw_HazardCmdOnTime = 0;
T_UWORD ruw_HazardCmdOffTime = 0;

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

/*void PELC_TurnOnFullHazardLights(HW_CONFIG le_HWConfig){
	
}*/

void PELC_SetHazardCmd(void){
	
	static T_UBYTE lub_CountHazardOnTime = 0;
	static T_UBYTE lub_CountHazardOffTime = 0;
	
	if(re_HazardCmdState == E_HAZARD_CMD_ACTIVE){
		
		if(re_HazardLState == E_HAZARDL_INACTIVE){
			re_HazardLState = E_HAZARDL_ACTIVE_ON;
		} 
		
	} else if(re_HazardLState == E_HAZARDL_ACTIVE_OFF && lub_CountHazardOffTime == ruw_HazardCmdOffTime){
				re_HazardLState = E_HAZARDL_INACTIVE;
			
				lub_CountHazardOffTime = 0;
				lub_CountHazardOnTime = 0;
				
			} 
	
	if(lub_CountHazardOnTime == ruw_HazardCmdOnTime){
		re_HazardLState = E_HAZARDL_ACTIVE_OFF;
		lub_CountHazardOnTime = 0;	
	}
	
	if(lub_CountHazardOffTime == ruw_HazardCmdOffTime){
		re_HazardLState = E_HAZARDL_ACTIVE_ON;
		lub_CountHazardOffTime = 0;	
	}
	
	if(re_HazardLState == E_HAZARDL_ACTIVE_ON){
		lub_CountHazardOnTime++;
	}else if(re_HazardLState == E_HAZARDL_ACTIVE_OFF){
				lub_CountHazardOffTime++;
			}
		
}

void PELC_SetTurnCmd(void){
	
	static T_UBYTE lub_CountTurnOnTime = 0;
	static T_UBYTE lub_CountTurnOffTime = 0;
	
	if(re_TurnCmdState == E_TURN_CMD_ACTIVE){
		
		if(re_TurnLState == E_TURNL_INACTIVE){
			re_TurnLState = E_TURNL_ACTIVE_ON;
		} 
		
	} else if(re_TurnLState == E_TURNL_ACTIVE_OFF && lub_CountTurnOffTime == ruw_TurnCmdOffTime){
				re_TurnLState = E_TURNL_INACTIVE;
			
				lub_CountTurnOffTime = 0;
				lub_CountTurnOnTime = 0;
				
			} 
	
	if(lub_CountTurnOnTime == ruw_TurnCmdOnTime){
		re_TurnLState = E_TURNL_ACTIVE_OFF;
		lub_CountTurnOnTime = 0;	
	}
	
	if(lub_CountTurnOffTime == ruw_TurnCmdOffTime){
		re_TurnLState = E_TURNL_ACTIVE_ON;
		lub_CountTurnOffTime = 0;	
	}
	
	if(re_TurnLState == E_TURNL_ACTIVE_ON){
		lub_CountTurnOnTime++;
	}else if(re_TurnLState == E_TURNL_ACTIVE_OFF){
				lub_CountTurnOffTime++;
			}
	
}

void PELC_SetStdLights(void){

	switch(re_HazardLState){
		
		case E_HAZARDL_ACTIVE_ON:
			PELC_TurnOnFull(PARKL_FL_PCR);
			PELC_TurnOnFull(PARKL_FR_PCR);
			PELC_TurnOnFull(BLINKERL_FL_PCR);
			PELC_TurnOnFull(BLINKERL_FR_PCR);
			PELC_TurnOnFull(BLINKERL_RL1_PCR);
			PELC_TurnOnFull(BLINKERL_RL2_PCR);
			PELC_TurnOnFull(BLINKERL_RL3_PCR);
			PELC_TurnOnFull(BLINKERL_RR1_PCR);
			PELC_TurnOnFull(BLINKERL_RR2_PCR);
			PELC_TurnOnFull(BLINKERL_RR3_PCR);
			break;
		
		case E_HAZARDL_ACTIVE_OFF:
			
			switch(re_MainLightsCmdState){
				
				case E_OFF:
					PELC_TurnOff(PARKL_FL_PCR);
					PELC_TurnOff(PARKL_FR_PCR);
					PELC_TurnOff(BLINKERL_FL_PCR);
					PELC_TurnOff(BLINKERL_FR_PCR);
					break;
					
				case E_DAY:
					PELC_TurnOnLevel(PARKL_FL_PCR, PARKL_FL_PWMCH, 20, 63);
					PELC_TurnOnLevel(PARKL_FR_PCR, PARKL_FR_PWMCH, 20, 63);
					PELC_TurnOnLevel(BLINKERL_FL_PCR, BLINKERL_FL_PWMCH, 20, 63);
					PELC_TurnOnLevel(BLINKERL_FR_PCR, BLINKERL_FR_PWMCH, 20, 63);
					break;
					
				case E_FULL:
					PELC_TurnOnLevel(PARKL_FL_PCR, PARKL_FL_PWMCH, 20, 63);
					PELC_TurnOnLevel(PARKL_FR_PCR, PARKL_FR_PWMCH, 20, 63);
					PELC_TurnOnLevel(BLINKERL_FL_PCR, BLINKERL_FL_PWMCH, 20, 63);
					PELC_TurnOnLevel(BLINKERL_FR_PCR, BLINKERL_FR_PWMCH, 20, 63);
					break;
					
				case E_AUTO:
					if(ruw_LightLevel < ruw_LightLevelPrev){
						if(ruw_LightLevel>=LIGHT_MIN_THR && ruw_LightLevel<LIGHT_NIGHT_THR){
							PELC_TurnOnLevel(PARKL_FL_PCR, PARKL_FL_PWMCH, 20, 63);
							PELC_TurnOnLevel(PARKL_FR_PCR, PARKL_FR_PWMCH, 20, 63);
							PELC_TurnOnLevel(BLINKERL_FL_PCR, BLINKERL_FL_PWMCH, 20, 63);
							PELC_TurnOnLevel(BLINKERL_FR_PCR, BLINKERL_FR_PWMCH, 20, 63);
						}
						
						if(ruw_LightLevel>=LIGHT_NIGHT_THR && ruw_LightLevel<LIGHT_AFT_THR){
							PELC_TurnOnLevel(PARKL_FL_PCR, PARKL_FL_PWMCH, 20, 63);
							PELC_TurnOnLevel(PARKL_FR_PCR, PARKL_FR_PWMCH, 20, 63);
							PELC_TurnOnLevel(BLINKERL_FL_PCR, BLINKERL_FL_PWMCH, 20, 63);
							PELC_TurnOnLevel(BLINKERL_FR_PCR, BLINKERL_FR_PWMCH, 20, 63);
						}
						
						if(ruw_LightLevel>=LIGHT_AFT_THR && ruw_LightLevel<=LIGHT_MAX_THR){
							PELC_TurnOff(PARKL_FL_PCR);
							PELC_TurnOff(PARKL_FR_PCR);
							PELC_TurnOff(BLINKERL_FL_PCR);
							PELC_TurnOff(BLINKERL_FR_PCR);
						}
						
					} else if(ruw_LightLevel >= ruw_LightLevelPrev){
					
						if(ruw_LightLevel>=LIGHT_MIN_THR && ruw_LightLevel<LIGHT_DAWN_THR){
							PELC_TurnOnLevel(PARKL_FL_PCR, PARKL_FL_PWMCH, 20, 63);
							PELC_TurnOnLevel(PARKL_FR_PCR, PARKL_FR_PWMCH, 20, 63);
							PELC_TurnOnLevel(BLINKERL_FL_PCR, BLINKERL_FL_PWMCH, 20, 63);
							PELC_TurnOnLevel(BLINKERL_FR_PCR, BLINKERL_FR_PWMCH, 20, 63);
						}
						
						if(ruw_LightLevel>=LIGHT_DAWN_THR && ruw_LightLevel<LIGHT_DAY_THR){
							PELC_TurnOnLevel(PARKL_FL_PCR, PARKL_FL_PWMCH, 20, 63);
							PELC_TurnOnLevel(PARKL_FR_PCR, PARKL_FR_PWMCH, 20, 63);
							PELC_TurnOnLevel(BLINKERL_FL_PCR, BLINKERL_FL_PWMCH, 20, 63);
							PELC_TurnOnLevel(BLINKERL_FR_PCR, BLINKERL_FR_PWMCH, 20, 63);
						}
						
						if(ruw_LightLevel>=LIGHT_DAY_THR && ruw_LightLevel<=LIGHT_MAX_THR){
							PELC_TurnOff(PARKL_FL_PCR);
							PELC_TurnOff(PARKL_FR_PCR);
							PELC_TurnOff(BLINKERL_FL_PCR);
							PELC_TurnOff(BLINKERL_FR_PCR);
						}
					}
					break;
				
			}		
			
			PELC_TurnOff(BLINKERL_RL1_PCR);
			PELC_TurnOff(BLINKERL_RL2_PCR);
			PELC_TurnOff(BLINKERL_RL3_PCR);
			PELC_TurnOff(BLINKERL_RR1_PCR);
			PELC_TurnOff(BLINKERL_RR2_PCR);
			PELC_TurnOff(BLINKERL_RR3_PCR);	
			break;
		
		case E_HAZARDL_INACTIVE:
			
			switch(re_TurnLState){
				
				case E_TURNL_ACTIVE_ON:
					
					if(re_TurnCmdSide == E_TURN_RIGHT){
						PELC_TurnOnFull(PARKL_FR_PCR);
						PELC_TurnOnFull(BLINKERL_FR_PCR);
						PELC_TurnOnFull(BLINKERL_RR1_PCR);
						PELC_TurnOnFull(BLINKERL_RR2_PCR);
						PELC_TurnOnFull(BLINKERL_RR3_PCR);
					}else{
						PELC_TurnOnFull(PARKL_FL_PCR);
						PELC_TurnOnFull(BLINKERL_FL_PCR);
						PELC_TurnOnFull(BLINKERL_RL1_PCR);
						PELC_TurnOnFull(BLINKERL_RL2_PCR);
						PELC_TurnOnFull(BLINKERL_RL3_PCR);
					}
					break;
					
				case E_TURNL_ACTIVE_OFF:
					
					switch(re_MainLightsCmdState){
				
						case E_OFF:
							PELC_TurnOff(PARKL_FL_PCR);
							PELC_TurnOff(PARKL_FR_PCR);
							PELC_TurnOff(BLINKERL_FL_PCR);
							PELC_TurnOff(BLINKERL_FR_PCR);
							break;
							
						case E_DAY:
							PELC_TurnOnLevel(PARKL_FL_PCR, PARKL_FL_PWMCH, 20, 63);
							PELC_TurnOnLevel(PARKL_FR_PCR, PARKL_FR_PWMCH, 20, 63);
							PELC_TurnOnLevel(BLINKERL_FL_PCR, BLINKERL_FL_PWMCH, 20, 63);
							PELC_TurnOnLevel(BLINKERL_FR_PCR, BLINKERL_FR_PWMCH, 20, 63);
							break;
							
						case E_FULL:
							PELC_TurnOnLevel(PARKL_FL_PCR, PARKL_FL_PWMCH, 20, 63);
							PELC_TurnOnLevel(PARKL_FR_PCR, PARKL_FR_PWMCH, 20, 63);
							PELC_TurnOnLevel(BLINKERL_FL_PCR, BLINKERL_FL_PWMCH, 20, 63);
							PELC_TurnOnLevel(BLINKERL_FR_PCR, BLINKERL_FR_PWMCH, 20, 63);
							break;
							
						case E_AUTO:
							if(ruw_LightLevel < ruw_LightLevelPrev){
								if(ruw_LightLevel>=LIGHT_MIN_THR && ruw_LightLevel<LIGHT_NIGHT_THR){
									PELC_TurnOnLevel(PARKL_FL_PCR, PARKL_FL_PWMCH, 20, 63);
									PELC_TurnOnLevel(PARKL_FR_PCR, PARKL_FR_PWMCH, 20, 63);
									PELC_TurnOnLevel(BLINKERL_FL_PCR, BLINKERL_FL_PWMCH, 20, 63);
									PELC_TurnOnLevel(BLINKERL_FR_PCR, BLINKERL_FR_PWMCH, 20, 63);
								}
								
								if(ruw_LightLevel>=LIGHT_NIGHT_THR && ruw_LightLevel<LIGHT_AFT_THR){
									PELC_TurnOnLevel(PARKL_FL_PCR, PARKL_FL_PWMCH, 20, 63);
									PELC_TurnOnLevel(PARKL_FR_PCR, PARKL_FR_PWMCH, 20, 63);
									PELC_TurnOnLevel(BLINKERL_FL_PCR, BLINKERL_FL_PWMCH, 20, 63);
									PELC_TurnOnLevel(BLINKERL_FR_PCR, BLINKERL_FR_PWMCH, 20, 63);
								}
								
								if(ruw_LightLevel>=LIGHT_AFT_THR && ruw_LightLevel<=LIGHT_MAX_THR){
									PELC_TurnOff(PARKL_FL_PCR);
									PELC_TurnOff(PARKL_FR_PCR);
									PELC_TurnOff(BLINKERL_FL_PCR);
									PELC_TurnOff(BLINKERL_FR_PCR);
								}
								
							} else if(ruw_LightLevel >= ruw_LightLevelPrev){
							
								if(ruw_LightLevel>=LIGHT_MIN_THR && ruw_LightLevel<LIGHT_DAWN_THR){
									PELC_TurnOnLevel(PARKL_FL_PCR, PARKL_FL_PWMCH, 20, 63);
									PELC_TurnOnLevel(PARKL_FR_PCR, PARKL_FR_PWMCH, 20, 63);
									PELC_TurnOnLevel(BLINKERL_FL_PCR, BLINKERL_FL_PWMCH, 20, 63);
									PELC_TurnOnLevel(BLINKERL_FR_PCR, BLINKERL_FR_PWMCH, 20, 63);
								}
								
								if(ruw_LightLevel>=LIGHT_DAWN_THR && ruw_LightLevel<LIGHT_DAY_THR){
									PELC_TurnOnLevel(PARKL_FL_PCR, PARKL_FL_PWMCH, 20, 63);
									PELC_TurnOnLevel(PARKL_FR_PCR, PARKL_FR_PWMCH, 20, 63);
									PELC_TurnOnLevel(BLINKERL_FL_PCR, BLINKERL_FL_PWMCH, 20, 63);
									PELC_TurnOnLevel(BLINKERL_FR_PCR, BLINKERL_FR_PWMCH, 20, 63);
								}
								
								if(ruw_LightLevel>=LIGHT_DAY_THR && ruw_LightLevel<=LIGHT_MAX_THR){
									PELC_TurnOff(PARKL_FL_PCR);
									PELC_TurnOff(PARKL_FR_PCR);
									PELC_TurnOff(BLINKERL_FL_PCR);
									PELC_TurnOff(BLINKERL_FR_PCR);
								}
							}
							break;
						
					}		
					
					PELC_TurnOff(BLINKERL_RL1_PCR);
					PELC_TurnOff(BLINKERL_RL2_PCR);
					PELC_TurnOff(BLINKERL_RL3_PCR);
					PELC_TurnOff(BLINKERL_RR1_PCR);
					PELC_TurnOff(BLINKERL_RR2_PCR);
					PELC_TurnOff(BLINKERL_RR3_PCR);					
					break;
				
				case E_TURNL_INACTIVE:
					break;
				
			}
			
			break;
		
		default:
			break;
	}
	
	switch(re_StopCmdState){
	
		case E_STOP_ACTIVE:
			PELC_TurnOnFull(PARKL_RL_PCR);
			PELC_TurnOnFull(PARKL_RR_PCR);
			PELC_TurnOnFull(STOPL_RL_PCR);
			PELC_TurnOnFull(STOPL_RR_PCR);
			break;
		
		case E_STOP_INACTIVE:
			
			switch(re_MainLightsCmdState){
				
				case E_OFF:
					PELC_TurnOff(PARKL_RL_PCR);
					PELC_TurnOff(PARKL_RR_PCR);
					PELC_TurnOff(STOPL_RL_PCR);
					PELC_TurnOff(STOPL_RR_PCR);
					break;
					
				case E_DAY:
					PELC_TurnOnLevel(PARKL_RL_PCR, PARKL_RL_PWMCH, 20, 63);
					PELC_TurnOnLevel(PARKL_RR_PCR, PARKL_RR_PWMCH, 20, 63);
					PELC_TurnOnLevel(STOPL_RL_PCR, PARKL_RL_PWMCH, 20, 63);
					PELC_TurnOnLevel(STOPL_RR_PCR, PARKL_RR_PWMCH, 20, 63);
					break;
					
				case E_FULL:
					PELC_TurnOnLevel(PARKL_RL_PCR, PARKL_RL_PWMCH, 20, 63);
					PELC_TurnOnLevel(PARKL_RR_PCR, PARKL_RR_PWMCH, 20, 63);
					PELC_TurnOnLevel(STOPL_RL_PCR, PARKL_RL_PWMCH, 20, 63);
					PELC_TurnOnLevel(STOPL_RR_PCR, PARKL_RR_PWMCH, 20, 63);
					break;
					
				case E_AUTO:
					if(ruw_LightLevel < ruw_LightLevelPrev){
						if(ruw_LightLevel>=LIGHT_MIN_THR && ruw_LightLevel<LIGHT_NIGHT_THR){
							PELC_TurnOnLevel(PARKL_RL_PCR, PARKL_RL_PWMCH, 20, 63);
							PELC_TurnOnLevel(PARKL_RR_PCR, PARKL_RR_PWMCH, 20, 63);
							PELC_TurnOnLevel(STOPL_RL_PCR, PARKL_RL_PWMCH, 20, 63);
							PELC_TurnOnLevel(STOPL_RR_PCR, PARKL_RR_PWMCH, 20, 63);
						}
						
						if(ruw_LightLevel>=LIGHT_NIGHT_THR && ruw_LightLevel<LIGHT_AFT_THR){
							PELC_TurnOnLevel(PARKL_RL_PCR, PARKL_RL_PWMCH, 20, 63);
							PELC_TurnOnLevel(PARKL_RR_PCR, PARKL_RR_PWMCH, 20, 63);
							PELC_TurnOnLevel(STOPL_RL_PCR, PARKL_RL_PWMCH, 20, 63);
							PELC_TurnOnLevel(STOPL_RR_PCR, PARKL_RR_PWMCH, 20, 63);
						}
						
						if(ruw_LightLevel>=LIGHT_AFT_THR && ruw_LightLevel<=LIGHT_MAX_THR){
							PELC_TurnOff(PARKL_RL_PCR);
							PELC_TurnOff(PARKL_RR_PCR);
							PELC_TurnOff(STOPL_RL_PCR);
							PELC_TurnOff(STOPL_RR_PCR);
						}
						
					} else if(ruw_LightLevel >= ruw_LightLevelPrev){
					
						if(ruw_LightLevel>=LIGHT_MIN_THR && ruw_LightLevel<LIGHT_DAWN_THR){
							PELC_TurnOnLevel(PARKL_RL_PCR, PARKL_RL_PWMCH, 20, 63);
							PELC_TurnOnLevel(PARKL_RR_PCR, PARKL_RR_PWMCH, 20, 63);
							PELC_TurnOnLevel(STOPL_RL_PCR, PARKL_RL_PWMCH, 20, 63);
							PELC_TurnOnLevel(STOPL_RR_PCR, PARKL_RR_PWMCH, 20, 63);
						}
						
						if(ruw_LightLevel>=LIGHT_DAWN_THR && ruw_LightLevel<LIGHT_DAY_THR){
							PELC_TurnOnLevel(PARKL_RL_PCR, PARKL_RL_PWMCH, 20, 63);
							PELC_TurnOnLevel(PARKL_RR_PCR, PARKL_RR_PWMCH, 20, 63);
							PELC_TurnOnLevel(STOPL_RL_PCR, PARKL_RL_PWMCH, 20, 63);
							PELC_TurnOnLevel(STOPL_RR_PCR, PARKL_RR_PWMCH, 20, 63);
						}
						
						if(ruw_LightLevel>=LIGHT_DAY_THR && ruw_LightLevel<=LIGHT_MAX_THR){
							PELC_TurnOff(PARKL_RL_PCR);
							PELC_TurnOff(PARKL_RR_PCR);
							PELC_TurnOff(STOPL_RL_PCR);
							PELC_TurnOff(STOPL_RR_PCR);
						}
					}
					break;
				
			}
			break;
		
		default:
			break;
	}
	
	switch(re_MainLightsCmdState){
	
		case E_OFF:
			PELC_TurnOff(HEADL_FL_PCR);
			PELC_TurnOff(HEADL_FR_PCR);
			break;
			
		case E_DAY:
			PELC_TurnOff(HEADL_FL_PCR);
			PELC_TurnOff(HEADL_FR_PCR);
			break;
			
		case E_FULL:
			PELC_TurnOnFull(HEADL_FL_PCR);
			PELC_TurnOnFull(HEADL_FR_PCR);
			break;
			
		case E_AUTO:
			if(ruw_LightLevel < ruw_LightLevelPrev){
				if(ruw_LightLevel>=LIGHT_MIN_THR && ruw_LightLevel<LIGHT_NIGHT_THR){
					PELC_TurnOnFull(HEADL_FL_PCR);
					PELC_TurnOnFull(HEADL_FR_PCR);			
				}
				
				if(ruw_LightLevel>=LIGHT_NIGHT_THR && ruw_LightLevel<LIGHT_AFT_THR){
					PELC_TurnOff(HEADL_FL_PCR);
					PELC_TurnOff(HEADL_FR_PCR);
				}
				
				if(ruw_LightLevel>=LIGHT_AFT_THR && ruw_LightLevel<=LIGHT_MAX_THR){
					PELC_TurnOff(HEADL_FL_PCR);
					PELC_TurnOff(HEADL_FR_PCR);					
				}
				
			} else if(ruw_LightLevel >= ruw_LightLevelPrev){
			
				if(ruw_LightLevel>=LIGHT_MIN_THR && ruw_LightLevel<LIGHT_DAWN_THR){
					PELC_TurnOnFull(HEADL_FL_PCR);
					PELC_TurnOnFull(HEADL_FR_PCR);
				}
				
				if(ruw_LightLevel>=LIGHT_DAWN_THR && ruw_LightLevel<LIGHT_DAY_THR){
					PELC_TurnOff(HEADL_FL_PCR);
					PELC_TurnOff(HEADL_FR_PCR);
				}
				
				if(ruw_LightLevel>=LIGHT_DAY_THR && ruw_LightLevel<=LIGHT_MAX_THR){
					PELC_TurnOff(HEADL_FL_PCR);
					PELC_TurnOff(HEADL_FR_PCR);
				}
			}
			break;
		
		default:
			break;
	}
	
}


void PELC_SetHighEndLights(void){

	switch(re_HazardLState){
		
		case E_HAZARDL_ACTIVE_ON:
			/*PELC_TurnOnFull(PARKL_FL_PCR);
			PELC_TurnOnFull(PARKL_FR_PCR);*/
			PELC_TurnOnFull(BLINKERL_FL_PCR);
			PELC_TurnOnFull(BLINKERL_FR_PCR);
			PELC_TurnOnFull(BLINKERL_RL1_PCR);
			PELC_TurnOnFull(BLINKERL_RL2_PCR);
			PELC_TurnOnFull(BLINKERL_RL3_PCR);
			PELC_TurnOnFull(BLINKERL_RR1_PCR);
			PELC_TurnOnFull(BLINKERL_RR2_PCR);
			PELC_TurnOnFull(BLINKERL_RR3_PCR);
			break;
		
		case E_HAZARDL_ACTIVE_OFF:			
			PELC_TurnOff(BLINKERL_FL_PCR);
			PELC_TurnOff(BLINKERL_FR_PCR);
			PELC_TurnOff(BLINKERL_RL1_PCR);
			PELC_TurnOff(BLINKERL_RL2_PCR);
			PELC_TurnOff(BLINKERL_RL3_PCR);
			PELC_TurnOff(BLINKERL_RR1_PCR);
			PELC_TurnOff(BLINKERL_RR2_PCR);
			PELC_TurnOff(BLINKERL_RR3_PCR);	
			break;
		
		case E_HAZARDL_INACTIVE:
			
			switch(re_TurnLState){
				
				case E_TURNL_ACTIVE_ON:
					
					if(re_TurnCmdSide == E_TURN_RIGHT){
						/*PELC_TurnOnFull(PARKL_FR_PCR);*/
						PELC_TurnOnFull(BLINKERL_FR_PCR);
						PELC_TurnOnFull(BLINKERL_RR1_PCR);
						PELC_TurnOnFull(BLINKERL_RR2_PCR);
						PELC_TurnOnFull(BLINKERL_RR3_PCR);
					}else{
						/*PELC_TurnOnFull(PARKL_FL_PCR);*/
						PELC_TurnOnFull(BLINKERL_FL_PCR);
						PELC_TurnOnFull(BLINKERL_RL1_PCR);
						PELC_TurnOnFull(BLINKERL_RL2_PCR);
						PELC_TurnOnFull(BLINKERL_RL3_PCR);
					}
					break;
					
				case E_TURNL_ACTIVE_OFF:
					PELC_TurnOff(BLINKERL_FR_PCR);
					PELC_TurnOff(BLINKERL_FL_PCR);				
					PELC_TurnOff(BLINKERL_RL1_PCR);
					PELC_TurnOff(BLINKERL_RL2_PCR);
					PELC_TurnOff(BLINKERL_RL3_PCR);
					PELC_TurnOff(BLINKERL_RR1_PCR);
					PELC_TurnOff(BLINKERL_RR2_PCR);
					PELC_TurnOff(BLINKERL_RR3_PCR);					
					break;
				
				case E_TURNL_INACTIVE:
					PELC_TurnOff(BLINKERL_FR_PCR);
					PELC_TurnOff(BLINKERL_FL_PCR);				
					PELC_TurnOff(BLINKERL_RL1_PCR);
					PELC_TurnOff(BLINKERL_RL2_PCR);
					PELC_TurnOff(BLINKERL_RL3_PCR);
					PELC_TurnOff(BLINKERL_RR1_PCR);
					PELC_TurnOff(BLINKERL_RR2_PCR);
					PELC_TurnOff(BLINKERL_RR3_PCR);
					break;
				
			}
			
			break;
		
		default:
			break;
	}
	
	switch(re_StopCmdState){ /* Stop cmd is controlled directly */
	
		case E_STOP_ACTIVE:
			PELC_TurnOnFull(STOPL_RL_PCR);
			PELC_TurnOnFull(STOPL_RR_PCR);
			break;
		
		case E_STOP_INACTIVE:
			PELC_TurnOff(STOPL_RL_PCR);
			PELC_TurnOff(STOPL_RR_PCR);			
			break;
		
		default:
			break;
	}
	
	switch(re_MainLightsCmdState){
	
		case E_OFF:
			PELC_TurnOff(HEADL_FL_PCR);
			PELC_TurnOff(HEADL_FR_PCR);
			PELC_TurnOff(PARKL_FR_PCR);
			PELC_TurnOff(PARKL_FL_PCR);
			PELC_TurnOff(PARKL_RR_PCR);
			PELC_TurnOff(PARKL_RL_PCR);
			break;
			
		case E_DAY:
			PELC_TurnOff(HEADL_FL_PCR);
			PELC_TurnOff(HEADL_FR_PCR);
			PELC_TurnOnFull(PARKL_FR_PCR);
			PELC_TurnOnFull(PARKL_FL_PCR);
			PELC_TurnOnFull(PARKL_RR_PCR);
			PELC_TurnOnFull(PARKL_RL_PCR);
			break;
			
		case E_FULL:
			PELC_TurnOnFull(HEADL_FL_PCR);
			PELC_TurnOnFull(HEADL_FR_PCR);
			PELC_TurnOnFull(PARKL_FR_PCR);
			PELC_TurnOnFull(PARKL_FL_PCR);
			PELC_TurnOnFull(PARKL_RR_PCR);
			PELC_TurnOnFull(PARKL_RL_PCR);
			break;
			
		case E_AUTO:
			if(ruw_LightLevel < ruw_LightLevelPrev){
				if(ruw_LightLevel>=LIGHT_MIN_THR && ruw_LightLevel<LIGHT_NIGHT_THR){
					PELC_TurnOnFull(HEADL_FL_PCR);
					PELC_TurnOnFull(HEADL_FR_PCR);
					PELC_TurnOnFull(PARKL_FR_PCR);
					PELC_TurnOnFull(PARKL_FL_PCR);
					PELC_TurnOnFull(PARKL_RR_PCR);
					PELC_TurnOnFull(PARKL_RL_PCR);			
				}
				
				if(ruw_LightLevel>=LIGHT_NIGHT_THR && ruw_LightLevel<LIGHT_AFT_THR){
					PELC_TurnOff(HEADL_FL_PCR);
					PELC_TurnOff(HEADL_FR_PCR);
					PELC_TurnOnFull(PARKL_FR_PCR);
					PELC_TurnOnFull(PARKL_FL_PCR);
					PELC_TurnOnFull(PARKL_RR_PCR);
					PELC_TurnOnFull(PARKL_RL_PCR);
				}
				
				if(ruw_LightLevel>=LIGHT_AFT_THR && ruw_LightLevel<=LIGHT_MAX_THR){
					PELC_TurnOff(HEADL_FL_PCR);
					PELC_TurnOff(HEADL_FR_PCR);
					PELC_TurnOff(PARKL_FR_PCR);
					PELC_TurnOff(PARKL_FL_PCR);
					PELC_TurnOff(PARKL_RR_PCR);
					PELC_TurnOff(PARKL_RL_PCR);					
				}
				
			} else if(ruw_LightLevel >= ruw_LightLevelPrev){
			
				if(ruw_LightLevel>=LIGHT_MIN_THR && ruw_LightLevel<LIGHT_DAWN_THR){
					PELC_TurnOnFull(HEADL_FL_PCR);
					PELC_TurnOnFull(HEADL_FR_PCR);
					PELC_TurnOnFull(PARKL_FR_PCR);
					PELC_TurnOnFull(PARKL_FL_PCR);
					PELC_TurnOnFull(PARKL_RR_PCR);
					PELC_TurnOnFull(PARKL_RL_PCR);
				}
				
				if(ruw_LightLevel>=LIGHT_DAWN_THR && ruw_LightLevel<LIGHT_DAY_THR){
					PELC_TurnOff(HEADL_FL_PCR);
					PELC_TurnOff(HEADL_FR_PCR);
					PELC_TurnOnFull(PARKL_FR_PCR);
					PELC_TurnOnFull(PARKL_FL_PCR);
					PELC_TurnOnFull(PARKL_RR_PCR);
					PELC_TurnOnFull(PARKL_RL_PCR);
				}
				
				if(ruw_LightLevel>=LIGHT_DAY_THR && ruw_LightLevel<=LIGHT_MAX_THR){
					PELC_TurnOff(HEADL_FL_PCR);
					PELC_TurnOff(HEADL_FR_PCR);
					PELC_TurnOff(PARKL_FR_PCR);
					PELC_TurnOff(PARKL_FL_PCR);
					PELC_TurnOff(PARKL_RR_PCR);
					PELC_TurnOff(PARKL_RL_PCR);
				}
			}
			break;
		
		default:
			break;
	}
	
}


void PELC_SetLuxuryLights(void){

	switch(re_HazardLState){
		
		case E_HAZARDL_ACTIVE_ON:
			/*PELC_TurnOnFull(PARKL_FL_PCR);
			PELC_TurnOnFull(PARKL_FR_PCR);*/
			PELC_TurnOnFull(BLINKERL_FL_PCR);
			PELC_TurnOnFull(BLINKERL_FR_PCR);
			PELC_TurnOnFull(BLINKERL_RL1_PCR);
			PELC_TurnOnFull(BLINKERL_RL2_PCR);
			PELC_TurnOnFull(BLINKERL_RL3_PCR);
			PELC_TurnOnFull(BLINKERL_RR1_PCR);
			PELC_TurnOnFull(BLINKERL_RR2_PCR);
			PELC_TurnOnFull(BLINKERL_RR3_PCR);
			break;
		
		case E_HAZARDL_ACTIVE_OFF:			
			PELC_TurnOff(BLINKERL_FL_PCR);
			PELC_TurnOff(BLINKERL_FR_PCR);
			PELC_TurnOff(BLINKERL_RL1_PCR);
			PELC_TurnOff(BLINKERL_RL2_PCR);
			PELC_TurnOff(BLINKERL_RL3_PCR);
			PELC_TurnOff(BLINKERL_RR1_PCR);
			PELC_TurnOff(BLINKERL_RR2_PCR);
			PELC_TurnOff(BLINKERL_RR3_PCR);	
			break;
		
		case E_HAZARDL_INACTIVE:
			
			switch(re_TurnLState){
				/* 
				
				Remember luxury will use rotabit
				
				*/
				case E_TURNL_ACTIVE_ON:
					
					if(re_TurnCmdSide == E_TURN_RIGHT){
						/*PELC_TurnOnFull(PARKL_FR_PCR);*/
						PELC_TurnOnFull(BLINKERL_FR_PCR);
						PELC_TurnOnFull(BLINKERL_RR1_PCR);
						PELC_TurnOnFull(BLINKERL_RR2_PCR);
						PELC_TurnOnFull(BLINKERL_RR3_PCR);
					}else{
						/*PELC_TurnOnFull(PARKL_FL_PCR);*/
						PELC_TurnOnFull(BLINKERL_FL_PCR);
						PELC_TurnOnFull(BLINKERL_RL1_PCR);
						PELC_TurnOnFull(BLINKERL_RL2_PCR);
						PELC_TurnOnFull(BLINKERL_RL3_PCR);
					}
					break;
					
				case E_TURNL_ACTIVE_OFF:
					PELC_TurnOff(BLINKERL_FR_PCR);
					PELC_TurnOff(BLINKERL_FL_PCR);				
					PELC_TurnOff(BLINKERL_RL1_PCR);
					PELC_TurnOff(BLINKERL_RL2_PCR);
					PELC_TurnOff(BLINKERL_RL3_PCR);
					PELC_TurnOff(BLINKERL_RR1_PCR);
					PELC_TurnOff(BLINKERL_RR2_PCR);
					PELC_TurnOff(BLINKERL_RR3_PCR);					
					break;
				
				case E_TURNL_INACTIVE:
					PELC_TurnOff(BLINKERL_FR_PCR);
					PELC_TurnOff(BLINKERL_FL_PCR);				
					PELC_TurnOff(BLINKERL_RL1_PCR);
					PELC_TurnOff(BLINKERL_RL2_PCR);
					PELC_TurnOff(BLINKERL_RL3_PCR);
					PELC_TurnOff(BLINKERL_RR1_PCR);
					PELC_TurnOff(BLINKERL_RR2_PCR);
					PELC_TurnOff(BLINKERL_RR3_PCR);
					break;
				
			}
			
			break;
		
		default:
			break;
	}
	
	switch(re_StopCmdState){ /* Stop cmd is controlled directly */
	
		case E_STOP_ACTIVE:
			PELC_TurnOnFull(STOPL_RL_PCR);
			PELC_TurnOnFull(STOPL_RR_PCR);
			break;
		
		case E_STOP_INACTIVE:
			PELC_TurnOff(STOPL_RL_PCR);
			PELC_TurnOff(STOPL_RR_PCR);			
			break;
		
		default:
			break;
	}
	
	switch(re_MainLightsCmdState){
	
		case E_OFF:
			PELC_TurnOff(HEADL_FL_PCR);
			PELC_TurnOff(HEADL_FR_PCR);
			PELC_TurnOff(PARKL_FR_PCR);
			PELC_TurnOff(PARKL_FL_PCR);
			PELC_TurnOff(PARKL_RR_PCR);
			PELC_TurnOff(PARKL_RL_PCR);
			break;
			
		case E_DAY:
			PELC_TurnOff(HEADL_FL_PCR);
			PELC_TurnOff(HEADL_FR_PCR);
			PELC_TurnOnFull(PARKL_FR_PCR);
			PELC_TurnOnFull(PARKL_FL_PCR);
			PELC_TurnOnFull(PARKL_RR_PCR);
			PELC_TurnOnFull(PARKL_RL_PCR);
			break;
			
		case E_FULL:
			PELC_TurnOnFull(HEADL_FL_PCR);
			PELC_TurnOnFull(HEADL_FR_PCR);
			PELC_TurnOnFull(PARKL_FR_PCR);
			PELC_TurnOnFull(PARKL_FL_PCR);
			PELC_TurnOnFull(PARKL_RR_PCR);
			PELC_TurnOnFull(PARKL_RL_PCR);
			break;
			
		case E_AUTO:
			if(ruw_LightLevel < ruw_LightLevelPrev){
				if(ruw_LightLevel>=LIGHT_MIN_THR && ruw_LightLevel<LIGHT_NIGHT_THR){
					PELC_TurnOnFull(HEADL_FL_PCR);
					PELC_TurnOnFull(HEADL_FR_PCR);
					PELC_TurnOnFull(PARKL_FR_PCR);
					PELC_TurnOnFull(PARKL_FL_PCR);
					PELC_TurnOnFull(PARKL_RR_PCR);
					PELC_TurnOnFull(PARKL_RL_PCR);			
				}
				
				if(ruw_LightLevel>=LIGHT_NIGHT_THR && ruw_LightLevel<LIGHT_AFT_THR){
					PELC_TurnOff(HEADL_FL_PCR);
					PELC_TurnOff(HEADL_FR_PCR);
					PELC_TurnOnFull(PARKL_FR_PCR);
					PELC_TurnOnFull(PARKL_FL_PCR);
					PELC_TurnOnFull(PARKL_RR_PCR);
					PELC_TurnOnFull(PARKL_RL_PCR);
				}
				
				if(ruw_LightLevel>=LIGHT_AFT_THR && ruw_LightLevel<=LIGHT_MAX_THR){
					PELC_TurnOff(HEADL_FL_PCR);
					PELC_TurnOff(HEADL_FR_PCR);
					PELC_TurnOff(PARKL_FR_PCR);
					PELC_TurnOff(PARKL_FL_PCR);
					PELC_TurnOff(PARKL_RR_PCR);
					PELC_TurnOff(PARKL_RL_PCR);					
				}
				
			} else if(ruw_LightLevel >= ruw_LightLevelPrev){
			
				if(ruw_LightLevel>=LIGHT_MIN_THR && ruw_LightLevel<LIGHT_DAWN_THR){
					PELC_TurnOnFull(HEADL_FL_PCR);
					PELC_TurnOnFull(HEADL_FR_PCR);
					PELC_TurnOnFull(PARKL_FR_PCR);
					PELC_TurnOnFull(PARKL_FL_PCR);
					PELC_TurnOnFull(PARKL_RR_PCR);
					PELC_TurnOnFull(PARKL_RL_PCR);
				}
				
				if(ruw_LightLevel>=LIGHT_DAWN_THR && ruw_LightLevel<LIGHT_DAY_THR){
					PELC_TurnOff(HEADL_FL_PCR);
					PELC_TurnOff(HEADL_FR_PCR);
					PELC_TurnOnFull(PARKL_FR_PCR);
					PELC_TurnOnFull(PARKL_FL_PCR);
					PELC_TurnOnFull(PARKL_RR_PCR);
					PELC_TurnOnFull(PARKL_RL_PCR);
				}
				
				if(ruw_LightLevel>=LIGHT_DAY_THR && ruw_LightLevel<=LIGHT_MAX_THR){
					PELC_TurnOff(HEADL_FL_PCR);
					PELC_TurnOff(HEADL_FR_PCR);
					PELC_TurnOff(PARKL_FR_PCR);
					PELC_TurnOff(PARKL_FL_PCR);
					PELC_TurnOff(PARKL_RR_PCR);
					PELC_TurnOff(PARKL_RL_PCR);
				}
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

void PELC_SendStatus_100MS(void){
	/*PELC_MsgSendStatus();*/
}

void PELC_GroupedTasks_100MS(void){
	static T_UBYTE lub_Counter = 0;
	
	lub_Counter++;
	
	if(lub_Counter == 10){
		
		PELC_SetHazardCmd();
		PELC_SetTurnCmd();
		
		switch(re_HWConfig){
			case E_STD:
				PELC_SetStdLights();
				break;
			
			case E_HIGH:
				PELC_SetHighEndLights();
				break;
				
			case E_LUX:
				PELC_SetLuxuryLights();
				break;
				
			default:
				break;
		}
		
		PELC_SendStatus_100MS();
		lub_Counter = 0;
	}
}

void PELC_ChkMsg_5MS(void){
	if(re_CANMsgHandlerState == E_MSG_RECEIVED){
		PELC_CmdMsgProcess();
	}
}

void PELC_GetLightLevel_500MS(void){
	
	static T_UBYTE lub_Counter = 0;
	
	lub_Counter++;
	
	if(lub_Counter == 50){
		ruw_LightLevelPrev = ruw_LightLevel;
		ruw_LightLevel = (T_UWORD)LightMeter_GetLightLevel();
		lub_Counter = 0;
	}
	
}