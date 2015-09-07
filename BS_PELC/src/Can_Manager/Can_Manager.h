/*~A*/
/*~+:Module Header*/
/*******************************************************************************/
/**
\file       Can_Manager.h
\brief      Provide Can Services
\author     Francisco Martinez
\version    1.0
\date       16/08/2015
*/
/*******************************************************************************/

#ifndef __CAN_MANAGER
#define __CAN_MANAGER

#include "Can.h"

extern void Can_Manager_PduHandler0(CAN_MessageDataType CanMessage);
extern void Can_Manager_PduHandler2(CAN_MessageDataType CanMessage);
extern void CanManager_SendMessage_12p5ms(void);
extern void CanManager_SendTestMessage_25ms(void);

extern CAN_MessageDataType CanMessage_PduHandler0;
extern CAN_MessageDataType CanMessage_PduHandler2;

#endif /* __CAN_MANAGER */
