/*~A*/
/*~+:Module Header*/
/*******************************************************************************/
/**
\file       Can_Manager.c
\brief      Provide Can Services
\author     Francisco Martinez
\version    1.0
\date       16/08/2015
*/
/*******************************************************************************/

#include "Can_Manager.h"
#include "PELC_MessageCtrl.h"

/* Temporary CAN Messages */
uint8_t dummy_msg2[8] = {0x33,0x44,0x55,0x66,0x88,0x89,0x45,0x4C};


/*CAN_PduType    pdu_handler2 = { 2, 2, dummy_msg2};*/
CAN_PduType    pdu_handler_test = { 2, 2, dummy_msg2};

uint32_t PduHandlerCnt0 = 0;
/*uint32_t PduHandlerCnt2 = 0;*/

CAN_MessageDataType CanMessage_PduHandler0;
/*CAN_MessageDataType CanMessage_PduHandler2;*/

void Can_Manager_PduHandler0(CAN_MessageDataType CanMessage)
{
	CanMessage_PduHandler0 = CanMessage;
	
	re_CANMsgHandlerState = E_MSG_RECEIVED;
	
	PduHandlerCnt0++;
}

/*void Can_Manager_PduHandler2(CAN_MessageDataType CanMessage)
{
	CanMessage_PduHandler2 = CanMessage;
	
	PduHandlerCnt2++;
}*/

void CanManager_SendTestMessage_25ms(void)
{
	CAN_SendFrame(pdu_handler_test);
}

