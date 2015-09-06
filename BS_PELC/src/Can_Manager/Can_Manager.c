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

/* Temporary CAN Messages */
/*uint8_t dummy_msg0[8] = {0xCA,0x83,0x15,0x77,0x19,0x56,0x65,0x00};
uint8_t dummy_msg1[8] = {0x00,0x65,0x56,0x19,0x77,0x15,0x83,0xCA};*/
uint8_t dummy_msg2[8] = {0x33,0x44,0x55,0x66,0x88,0x89,0x45,0x4C};

/*CAN_PduType    pdu_handler4 = { 4, 8, dummy_msg0};
CAN_PduType    pdu_handler5 = { 5, 6, dummy_msg1};*/
CAN_PduType    pdu_handler2 = { 2, 2, dummy_msg2};
CAN_PduType    pdu_handler_test = { 2, 2, dummy_msg2};
/*CAN_PduType    pdu_handler1 = { 7, 4, dummy_msg2};*/

uint32_t PduHandlerCnt0 = 0;
uint32_t PduHandlerCnt2 = 0;

CAN_MessageDataType CanMessage_PduHandler0;
CAN_MessageDataType CanMessage_PduHandler2;

void Can_Manager_PduHandler0(CAN_MessageDataType CanMessage)
{
	CanMessage_PduHandler0 = CanMessage;
	
	PduHandlerCnt0++;
}

void Can_Manager_PduHandler2(CAN_MessageDataType CanMessage)
{
	CanMessage_PduHandler2 = CanMessage;
	
	/*rub_ECU_DataLeft = */
	
	PduHandlerCnt2++;
}

void CanManager_SendMessage_12p5ms(void)
{
	/*CAN_SendFrame(pdu_handler4);
	CAN_SendFrame(pdu_handler5);*/
	
}

void CanManager_SendTestMessage_25ms(void)
{
	CAN_SendFrame(pdu_handler_test);
}

