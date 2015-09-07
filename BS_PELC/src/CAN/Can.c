/*~A*/
/*~+:Header*/
/*******************************************************************************/
/**
\file       can.c
\author     Alicia Álvarez
\version    1.0
*/
/****************************************************************************************************/
/*~E*/
/*~A*/
/*~+:Imports*/
#include "Can.h"
#include "IntcInterrupts.h"
/*~E*/
/*~A*/
/*~+:Variables*/
FLEXCAN2_Type                   *bios_cnf_can_eng[2];
CAN_ConfigDeviceType          *can_config_dev_ptr[2];
CAN_ConfigType                 *can_config_ptr;
/* Containers for the RXD and TXD messages per MB*/
CAN_MessageDataType           received_messages[64];
CAN_MessageDataType           txd_messages[64];
/*~E*/
/*~A*/
/*~+:Private Operations*/
/*~A*/
/*~+:uint8_t CAN_SendFrameInt(uint8_t can_eng, uint8_t can_channel, uint8_t *can_msg_buf, uint8_t len)*/
uint8_t CAN_SendFrameInt(uint8_t can_eng, uint8_t can_channel, uint8_t *can_msg_buf, uint8_t len){
uint8_t i;
			uint8_t temp = can_msg_buf[0];
/*~A*/
/*~+:Hints*/
/* 
Check for FIFO operation if it is enabled (IF: the BUF7 down to BUF0 MB functionality for the buffers 
that are being used for this example BUF4 down to BUF0  are not used whhich means that they are reserved
With FIFO operation:
BUF7I: FIFO Overflow
BUF6I: FIFO almost full
BUF5I: Frames available in the FIFO
IF's are in normal operation when FIFO is not enabled
When FIFO is enabled the memory area from 0x80 to 0xFC (which is normally occupied by MBs 0 to 7)
is used by the reception FIFO engine 
*/

/* Abort Transmission AEN must be set otherwise just writing 8 to CODE*/
/* Considering the buffer messages used are from 0 to 31 and they are not multiplexed */
/*~E*/
bios_cnf_can_eng[can_eng]->BUF[can_channel].CS.B.CODE = 0x8; /* MB Tx not Active */
/*  In case the Abort Mechanism is enabled.
bios_cnf_can_eng[can_eng]->BUF[can_channel].CS.B.CODE = 0x9;  MB Abort code Tx
if (bios_cnf_can_eng[can_eng]->BUF[can_channel].CS.B.CODE != 0x09){
while( ( (bios_cnf_can_eng[can_eng]->IFRL.R >> can_channel) & 0x1)   != 0x1){};  Waits for Frame to be Transmitted
}
After this reading the CODE field ...
if (CAN_A.BUF[1].CS.B.CODE == 0x09) Message was Aborted
if (CAN_A.BUF[1].CS.B.CODE == 0x08) Message was transmitted
*/
if (can_channel<32)
{
bios_cnf_can_eng[can_eng]->IFRL.R |= (0x1 << can_channel); /* Corresponding IFLAG must be cleared */
}
else
{
bios_cnf_can_eng[can_eng]->IFRH.R |= (0x1 << (can_channel-32)); /* Corresponding IFLAG must be cleared */
}


/* Write ID word */

/* PRIO has not effect if LBUF is enabled, it'd be ok if that bit in config structure is read here */
//bios_cnf_can_eng[can_eng]->BUF[can_channel].ID.B.PRIO = 0x0; /* Message configured with the Highest priority */
//bios_cnf_can_eng[can_eng]->BUF[can_channel].ID.B.STD_ID = can_config_dev_ptr[can_eng]->can_dev_messages[can_channel].can_msg_config[0].can_msg_id; /* ID Configured in Standard Frame (IDE = 0) */

/* Write LENGTH and DATA BYTES */
bios_cnf_can_eng[can_eng]->BUF[can_channel].CS.B.LENGTH = len; /* Set DLC of MB Format (Bytes to be transmitted)  */
for (i=0; i<len;  i++){
bios_cnf_can_eng[can_eng]->BUF[can_channel].DATA.B[i] = can_msg_buf[i];
/*bios_cnf_can_eng[can_eng]->BUF[can_channel].DATA.B[i] = *(can_msg_buf+i);*/
}

/* Write Control & Code Fields */

bios_cnf_can_eng[can_eng]->BUF[can_channel].CS.B.RTR = can_config_dev_ptr[can_eng]->can_dev_messages[can_channel].can_msg_rtr; /* Data Frame to be transmitted */
bios_cnf_can_eng[can_eng]->BUF[can_channel].CS.B.CODE = 0xC; /* Transmit Data Frame */
return (0);
}
/*~E*/
/*~A*/
/*~+:void CANB_TxIsr(uint8_t message_buffer)*/
void CANB_TxIsr(uint8_t message_buffer)
{
uint8_t data_idx;
uint8_t code;
uint8_t dummy;

uint8_t idx_tx_msg=0;
/*~A*/
/*~+:Transmission*/
/*~A*/
/*~+:Get ID*/
if (bios_cnf_can_eng[CANB]->BUF[message_buffer].CS.B.IDE) 
{
/*Extended ID */
txd_messages[message_buffer].msg_id_field = (bios_cnf_can_eng[CANB]->BUF[message_buffer].ID.R) & (uint32_t)(0x1FFFFFFF);

}
else
{
/* Standard ID */
txd_messages[message_buffer].msg_id_field = (bios_cnf_can_eng[CANB]->BUF[message_buffer].ID.B.STD_ID) & (uint32_t)0x7FF;
}
/*~E*/
txd_messages[message_buffer].msg_buff_nr = message_buffer;
txd_messages[message_buffer].msg_ide = (uint8_t)bios_cnf_can_eng[CANB]->BUF[message_buffer].CS.B.IDE;
txd_messages[message_buffer].msg_time_stamp = (uint16_t)bios_cnf_can_eng[CANB]->BUF[message_buffer].CS.B.TIMESTAMP;
txd_messages[message_buffer].msg_dlc_field = (uint8_t)bios_cnf_can_eng[CANB]->BUF[message_buffer].CS.B.LENGTH;
code = (uint8_t)bios_cnf_can_eng[CANB]->BUF[message_buffer].CS.B.CODE;
for (data_idx=0; data_idx<(txd_messages[message_buffer].msg_dlc_field); data_idx++) {
txd_messages[message_buffer].msg_data_field[data_idx] = bios_cnf_can_eng[CANB]->BUF[message_buffer].DATA.B[data_idx];
}
/* Read TIMER to unlock message buffers */
dummy = (uint8_t)bios_cnf_can_eng[CANB]->TIMER.R;

if ( NULL != can_config_dev_ptr[0]->can_dev_messages[message_buffer].CallbackFcnt )
{
can_config_dev_ptr[0]->can_dev_messages[message_buffer].CallbackFcnt(txd_messages[message_buffer]);
}
/*~E*/
}
/*~E*/
/*~A*/
/*~+:void CANB_RxIsr(uint8_t message_buffer)*/
void CANB_RxIsr(uint8_t message_buffer)
{
uint8_t data_idx;
uint8_t code;
uint8_t dummy;

uint8_t idx_tx_msg=0;
/*~A*/
/*~+:Reception*/
/*~A*/
/*~+:Get ID*/
if (bios_cnf_can_eng[CANB]->BUF[message_buffer].CS.B.IDE) 
{
/*Extended ID */
received_messages[message_buffer].msg_id_field = (bios_cnf_can_eng[CANB]->BUF[message_buffer].ID.R) & (uint32_t)(0x1FFFFFFF);

}
else
{
/* Standard ID */
received_messages[message_buffer].msg_id_field = (bios_cnf_can_eng[CANB]->BUF[message_buffer].ID.B.STD_ID) & (uint32_t)0x7FF;
}
/*~E*/
received_messages[message_buffer].msg_buff_nr = message_buffer;
received_messages[message_buffer].msg_ide = (uint8_t)bios_cnf_can_eng[CANB]->BUF[message_buffer].CS.B.IDE;
received_messages[message_buffer].msg_time_stamp = (uint16_t)bios_cnf_can_eng[CANB]->BUF[message_buffer].CS.B.TIMESTAMP;
received_messages[message_buffer].msg_dlc_field = (uint8_t)bios_cnf_can_eng[CANB]->BUF[message_buffer].CS.B.LENGTH;
code = (uint8_t)bios_cnf_can_eng[CANB]->BUF[message_buffer].CS.B.CODE;
for (data_idx=0; data_idx<(received_messages[message_buffer].msg_dlc_field); data_idx++) {
received_messages[message_buffer].msg_data_field[data_idx] = bios_cnf_can_eng[CANB]->BUF[message_buffer].DATA.B[data_idx];
}
/* Read TIMER to unlock message buffers */
dummy = (uint8_t)bios_cnf_can_eng[CANB]->TIMER.R;

if ( NULL != can_config_dev_ptr[0]->can_dev_messages[message_buffer].CallbackFcnt )
{
can_config_dev_ptr[0]->can_dev_messages[message_buffer].CallbackFcnt(received_messages[message_buffer]);
}
/*~E*/
}
/*~E*/
/*~A*/
/*~+:void CANB_Isr(void)*/
void CANB_Isr(void)
{
uint8_t mb_idx;
uint8_t mask_flag;
for (mb_idx=0; mb_idx<can_config_ptr->can_device->can_nr_of_msg; mb_idx++){
if (mb_idx<32){
mask_flag = (uint8_t)( (bios_cnf_can_eng[CANB]->IFRL.R >> mb_idx) & 0x1);
}
else
{
mask_flag = (uint8_t)( (bios_cnf_can_eng[CANB]->IFRH.R >> (mb_idx-(uint8_t)32)) & 0x1);
}
if (mask_flag == 1){
/*~A*/
/*~+:Clear MB Flag*/
if (mb_idx<32){
bios_cnf_can_eng[CANB]->IFRL.R |= (0x1 << mb_idx);   /* Clear the MB Flag */
}
else
{
bios_cnf_can_eng[CANB]->IFRH.R |= (0x1 << (mb_idx-(uint8_t)32));   /* Clear the MB Flag */
}
/*~E*/
if ((bios_cnf_can_eng[CANB]->BUF[mb_idx].CS.B.CODE)<8)
{
CANB_RxIsr(mb_idx);
}
else
{
CANB_TxIsr(mb_idx);
}
}
else
{
/* No RX / TX*/
}
}
}
/*~E*/
/*~E*/
/*~A*/
/*~+:Public Operations*/
/*~A*/
/*~+:void CAN_Initialization(CAN_ConfigType *can_config)*/
void CAN_Initialization(CAN_ConfigType *can_config){
uint8_t dev_idx, mb_idx, message_buffer;
uint16_t delay = 2000;
can_config_ptr = can_config;
can_config_dev_ptr[0] = can_config_ptr->can_device;
bios_cnf_can_eng[0] = &CAN_0;
bios_cnf_can_eng[1] = &CAN_1;
/*~A*/
/*~+:Temporary configuration for CAN B - This belongs to IO Configuration*/
SIU.PCR[42].B.PA = 1; /* Primary function */
SIU.PCR[42].B.OBE = 1; /* Enable output buffer for the pad */
SIU.PCR[42].B.IBE = 0; /* 0 Disable input buffer for the pad */
/* SIU.PCR[42].B.DSC = 0; Not available on this MCU*/  /* 10 pF drive strength */
SIU.PCR[42].B.ODE = 0; /* Enable open drain for the pad */
/* SIU.PCR[42].B.HYS = 0; Not available on this MCU*/  /* Disable hysteresis for the pad */
SIU.PCR[42].B.SRC = 0; /* Minimum slew rate */
SIU.PCR[42].B.WPE = 0; /* Enable weak pull device for the pad */
SIU.PCR[42].B.WPS = 0; /* Pulldown is enabled for the pad */
/* Rx */
SIU.PSMI[0].B.PADSEL = 0x01; /* CAN1RX / FlexCAN_1 --> 01: PCR[43]*/
SIU.PCR[43].B.PA = 0; /* Primary function */
SIU.PCR[43].B.OBE = 0; /* 0 Disable output buffer for the pad */
SIU.PCR[43].B.IBE = 1; /* Enable input buffer for the pad */
/*SIU.PCR[43].B.DSC = 0; Not available on this MCU*/ /* 10 pF drive strength */
SIU.PCR[43].B.ODE = 0; /* Disable open drain for the pad */
/*SIU.PCR[43].B.HYS = 0; Not available on this MCU*/ /* Disable hysteresis for the pad */
SIU.PCR[43].B.SRC = 0; /* Minimum slew rate */
SIU.PCR[43].B.WPE = 0; /* Enable weak pull device for the pad */
SIU.PCR[43].B.WPS = 0; /* Pulldown is enabled for the pad */
/*~E*/
for (dev_idx=0; dev_idx<can_config_ptr->can_nr_of_devices; dev_idx++){
/*~A*/
/*~+:Device level initialization*/
/* Reset the CAN Module. No waiting for softreset confirmation */
bios_cnf_can_eng[can_config_dev_ptr[dev_idx]->can_eng_dev]->MCR.B.SOFTRST = 0x1;       
do
{
delay--; /* Wait for Soft Reset */
}
while ((bios_cnf_can_eng[can_config_dev_ptr[dev_idx]->can_eng_dev]->MCR.B.SOFTRST) && (delay > 0));

/* Entering Disable Mode */
bios_cnf_can_eng[can_config_dev_ptr[dev_idx]->can_eng_dev]->MCR.B.MDIS = 0x1;          /* Disable the CAN module */ 
bios_cnf_can_eng[can_config_dev_ptr[dev_idx]->can_eng_dev]->CR.B.CLKSRC = can_config_dev_ptr[dev_idx]->can_dev_baudrate->can_ctrl_clksrc;
/* FLEXCAN must be put in Freeze Mode before accessing (writing) into any of its configuration registers */
bios_cnf_can_eng[can_config_dev_ptr[dev_idx]->can_eng_dev]->MCR.B.MDIS = 0x0;          /* Module automatocally goes to FRZ mode once the clock source is selected and module is enabled */
bios_cnf_can_eng[can_config_dev_ptr[dev_idx]->can_eng_dev]->MCR.B.HALT = 0x1;          /* HALT bit is set */

bios_cnf_can_eng[can_config_dev_ptr[dev_idx]->can_eng_dev]->MCR.B.MAXMB= (uint32_t)(can_config_dev_ptr[dev_idx]->can_nr_of_msg-1);/* Enable the required MB */
bios_cnf_can_eng[can_config_dev_ptr[dev_idx]->can_eng_dev]->MCR.B.BCC = (uint32_t)can_config_dev_ptr[dev_idx]->can_ctrl_mbfen;/* Enable individual filtering per MB and reception */
bios_cnf_can_eng[can_config_dev_ptr[dev_idx]->can_eng_dev]->MCR.B.WRNEN = 0x0; /* Enable warning interrupts */
bios_cnf_can_eng[can_config_dev_ptr[dev_idx]->can_eng_dev]->MCR.B.SRXDIS = 0x1; /* Disable frame self reception */

bios_cnf_can_eng[can_config_dev_ptr[dev_idx]->can_eng_dev]->MCR.B.FEN = can_config_dev_ptr[dev_idx]->can_ctrl_fifo; /* Disable FIFO */
bios_cnf_can_eng[can_config_dev_ptr[dev_idx]->can_eng_dev]->MCR.B.AEN = 0x0; /* "DIS" Enable the Abort Mechanism */
bios_cnf_can_eng[can_config_dev_ptr[dev_idx]->can_eng_dev]->MCR.B.LPRIO_EN = 0x0; /* Enable the local priority feature */

for (mb_idx=0; mb_idx < 64; mb_idx++) /* Clear the MB's */
{
bios_cnf_can_eng[can_config_dev_ptr[dev_idx]->can_eng_dev]->BUF[mb_idx].CS.R = 0x0;
}
/* Initialize the Control Register */

/* Determine Timing Parameters */
bios_cnf_can_eng[can_config_dev_ptr[dev_idx]->can_eng_dev]->CR.B.LPB = 0; /* Loop Back disabled */
/* Selects the Clock Source */

bios_cnf_can_eng[can_config_dev_ptr[dev_idx]->can_eng_dev]->CR.B.PROPSEG = can_config_dev_ptr[dev_idx]->can_dev_baudrate->can_ctrl_propseg - 1;
bios_cnf_can_eng[can_config_dev_ptr[dev_idx]->can_eng_dev]->CR.B.PSEG1 = can_config_dev_ptr[dev_idx]->can_dev_baudrate->can_ctrl_pseg1 - 1;
bios_cnf_can_eng[can_config_dev_ptr[dev_idx]->can_eng_dev]->CR.B.PSEG2 = can_config_dev_ptr[dev_idx]->can_dev_baudrate->can_ctrl_pseg2 - 1;
bios_cnf_can_eng[can_config_dev_ptr[dev_idx]->can_eng_dev]->CR.B.RJW = can_config_dev_ptr[dev_idx]->can_dev_baudrate->can_ctrl_rjw - 1;
/* Determine Bit Rate */
bios_cnf_can_eng[can_config_dev_ptr[dev_idx]->can_eng_dev]->CR.B.PRESDIV = can_config_dev_ptr[dev_idx]->can_dev_baudrate->can_ctrl_presdiv - 1;

/* Determine the internal arbitration mode */
bios_cnf_can_eng[can_config_dev_ptr[dev_idx]->can_eng_dev]->CR.B.LBUF = can_config_dev_ptr[dev_idx]->can_ctrl_lbuf; /* Highest priority buffer is transmitted first */

/* Message Buffers and the RX individual mask registers are not affected by reset and they are not automatically initialized*/
/* Configure the Message Buffers and Mask's */
for (mb_idx=0; mb_idx < (can_config_dev_ptr[dev_idx]->can_nr_of_msg); mb_idx++){
message_buffer = can_config_dev_ptr[dev_idx]->can_dev_messages[mb_idx].can_msg;
bios_cnf_can_eng[can_config_dev_ptr[dev_idx]->can_eng_dev]->BUF[message_buffer].CS.B.IDE = can_config_dev_ptr[dev_idx]->can_dev_messages[mb_idx].can_msg_id_length; /* ID Format */
if (can_config_dev_ptr[dev_idx]->can_dev_messages[mb_idx].can_msg_id_length)
{
/* Extended ID */
bios_cnf_can_eng[can_config_dev_ptr[dev_idx]->can_eng_dev]->BUF[message_buffer].ID.R &= 0xE0000000;
bios_cnf_can_eng[can_config_dev_ptr[dev_idx]->can_eng_dev]->BUF[message_buffer].ID.R |= (uint32_t)can_config_dev_ptr[dev_idx]->can_dev_messages[mb_idx].can_msg_id;
bios_cnf_can_eng[can_config_dev_ptr[dev_idx]->can_eng_dev]->BUF[message_buffer].CS.B.SRR = 0x1; /* 0x1 for ID extended format */
}
else
{
/* Standard ID*/
bios_cnf_can_eng[can_config_dev_ptr[dev_idx]->can_eng_dev]->BUF[message_buffer].ID.B.STD_ID = can_config_dev_ptr[dev_idx]->can_dev_messages[mb_idx].can_msg_id;
bios_cnf_can_eng[can_config_dev_ptr[dev_idx]->can_eng_dev]->BUF[message_buffer].CS.B.SRR = 0x0; 
}
if (can_config_dev_ptr[dev_idx]->can_dev_messages[mb_idx].can_msg_op == CNF_CAN_CH_TX){
/* MB used for TX */
bios_cnf_can_eng[can_config_dev_ptr[dev_idx]->can_eng_dev]->BUF[message_buffer].CS.B.CODE = 0x8; /* 0x8 = MB TX not Active */

}
else{
/* MB used for RX */
bios_cnf_can_eng[can_config_dev_ptr[dev_idx]->can_eng_dev]->BUF[message_buffer].CS.B.CODE = 0x4; /* 0x4 = MB RX Active and Empty */
if (can_config_dev_ptr[dev_idx]->can_dev_messages[mb_idx].can_msg_id_length)
{
/* Extended Filter*/
/* Setting the RX IMASK's & Global Mask */
bios_cnf_can_eng[can_config_dev_ptr[dev_idx]->can_eng_dev]->RXIMR[message_buffer].R =(uint32_t) can_config_dev_ptr[dev_idx]->can_dev_messages[mb_idx].can_msg_mask;
}
else
{
/* Standard Filter */
/* Setting the RX IMASK's & Global Mask */
bios_cnf_can_eng[can_config_dev_ptr[dev_idx]->can_eng_dev]->RXIMR[message_buffer].R = (uint32_t)(0x0003FFFF)|((can_config_dev_ptr[dev_idx]->can_dev_messages[mb_idx].can_msg_mask)<<18);
}
}


/*~A*/
/*~+:Enable Interrupt for each Message Buffer*/
if ( NULL != can_config_dev_ptr[dev_idx]->can_dev_messages[mb_idx].CallbackFcnt )
{
if ( message_buffer < 32 ){
bios_cnf_can_eng[can_config_dev_ptr[dev_idx]->can_eng_dev]->IMRL.R |= (uint32_t)(1<<(message_buffer));
}
else
{
bios_cnf_can_eng[can_config_dev_ptr[dev_idx]->can_eng_dev]->IMRH.R |= (uint32_t)(1<<((message_buffer)-32));
}
}
/*~E*/
}
/* Negate the HALT bit to enable the module */
bios_cnf_can_eng[can_config_dev_ptr[dev_idx]->can_eng_dev]->MCR.B.HALT = 0x0;
bios_cnf_can_eng[can_config_dev_ptr[dev_idx]->can_eng_dev]->MCR.B.FRZ = 0x0;
/*~E*/
}
/*~A*/
/*~+:Temporary configuration for interrupt handler*/
/* Install Interrupt routine for all MB */
/*from interrupt vector table, IRQ #'s*/
INTC_InstallINTCInterruptHandler(CANB_Isr,88,4);
INTC_InstallINTCInterruptHandler(CANB_Isr,89,4);
INTC_InstallINTCInterruptHandler(CANB_Isr,90,4);
INTC_InstallINTCInterruptHandler(CANB_Isr,91,4);
INTC_InstallINTCInterruptHandler(CANB_Isr,92,4);
INTC_InstallINTCInterruptHandler(CANB_Isr,93,4);
/*~E*/
}
/*~E*/
/*~A*/
/*~+:void CAN_SendFrame(CAN_PduType pdu_handler)*/
void CAN_SendFrame(CAN_PduType pdu_handler){
/* CAN Engine ID -Driver ID-*/ 		if (can_config_ptr->can_device[0].can_dev_messages[pdu_handler.can_mb_nr].can_msg_op == CNF_CAN_CH_TX){
CAN_SendFrameInt(CANB,pdu_handler.can_mb_nr,pdu_handler.can_sdu,pdu_handler.can_dlc);
}
else
{
/* HTH not valid */
}
}
/*~E*/
/*~A*/
/*~+:void CAN_Stop(void)*/
void CAN_Stop(void){
uint8_t dev_idx;
uint32_t delay =200;
for (dev_idx=0; dev_idx<can_config_ptr->can_nr_of_devices; dev_idx++){
do
{
delay--; /* Wait for TX */
}
while (((bios_cnf_can_eng[can_config_dev_ptr[dev_idx]->can_eng_dev]->ESR.R & 0xC0) == 0x40 )&& (delay > 0));
bios_cnf_can_eng[can_config_dev_ptr[dev_idx]->can_eng_dev]->MCR.B.HALT = 1; /* Stop the module */
delay = 200;
bios_cnf_can_eng[can_config_dev_ptr[dev_idx]->can_eng_dev]->MCR.B.SOFTRST = 0x1;       /* Reset the CAN Module */
do
{
delay--; /* Wait for Soft Reset */
}
while ((bios_cnf_can_eng[can_config_dev_ptr[dev_idx]->can_eng_dev]->MCR.B.SOFTRST)  && (delay > 0));

/* Entering Disable Mode */
bios_cnf_can_eng[can_config_dev_ptr[dev_idx]->can_eng_dev]->MCR.B.MDIS = 0x1;          /* Disable the CAN module */ 
}
/* Disable Interrupt routines for all MB */
INTC_InstallINTCInterruptHandler(CANB_Isr,88,0);
INTC_InstallINTCInterruptHandler(CANB_Isr,89,0);
INTC_InstallINTCInterruptHandler(CANB_Isr,90,0);
INTC_InstallINTCInterruptHandler(CANB_Isr,91,0);
INTC_InstallINTCInterruptHandler(CANB_Isr,92,0);
INTC_InstallINTCInterruptHandler(CANB_Isr,93,0);
}
/*~E*/
/*~E*/
