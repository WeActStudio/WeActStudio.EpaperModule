/********************************** (C) COPYRIGHT *******************************
 * File Name          : usb_regs.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2019/10/15
 * Description        : Interface functions to USB cell registers
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * SPDX-License-Identifier: Apache-2.0
*******************************************************************************/ 
#include "usb_lib.h"

/*********************************************************************
 * @fn      SetCNTR.
 *
 * @brief   Set the CNTR register value.
 *
 * @param   wRegValue - new register value.
 *
 * @return  none
 */	
void SetCNTR(uint16_t wRegValue)
{
  _SetCNTR(wRegValue);
}

/*********************************************************************
 * @fn      GetCNTR.
 *
 * @brief   returns the CNTR register value.
 *
 * @return  CNTR register Value.
 */
uint16_t GetCNTR(void)
{
  return(_GetCNTR());
}

/*********************************************************************
 * @fn      SetISTR.
 *
 * @brief   Set the CNTR register value.
 *
 * @param   wRegValue - new register value.
 *
 * @return  none
 */	
void SetISTR(uint16_t wRegValue)
{
  _SetISTR(wRegValue);
}

/*********************************************************************
 * @fn      GetISTR
 *
 * @brief   Returns the ISTR register value.
 *
 * @return  ISTR register Value
 */
uint16_t GetISTR(void)
{
  return(_GetISTR());
}

/*********************************************************************
 * @fn      GetFNR
 *
 * @brief   Returns the FNR register value.
 *
 * @return  FNR register Value
 */
uint16_t GetFNR(void)
{
  return(_GetFNR());
}

/*********************************************************************
 * @fn      SetDADDR
 *
 * @brief   Set the DADDR register value.
 *
 * @param   wRegValue - new register value.
 *
 * @return  none
 */	
void SetDADDR(uint16_t wRegValue)
{
  _SetDADDR(wRegValue);
}

/*********************************************************************
 * @fn      GetDADDR
 *
 * @brief   Returns the DADDR register value.
 *
 * @return  DADDR register Value
 */
uint16_t GetDADDR(void)
{
  return(_GetDADDR());
}

/*********************************************************************
 * @fn      SetBTABLE
 *
 * @brief   Set the CNTR register value.
 *
 * @param   wRegValue - new register value.
 *
 * @return  none
 */	
void SetBTABLE(uint16_t wRegValue)
{
  _SetBTABLE(wRegValue);
}

/*********************************************************************
 * @fn      GetBTABLE.
 *
 * @brief   Returns the BTABLE register value.
 *
 * @return  BTABLE address.
 */	
uint16_t GetBTABLE(void)
{
  return(_GetBTABLE());
}

/*********************************************************************
 * @fn      SetENDPOINT
 *
 * @brief   Set the Endpoint register value.
 *
 * @param   bEpNum - Endpoint Number. 
 *          wRegValue.
 *
 * @return  none
 */	
void SetENDPOINT(uint8_t bEpNum, uint16_t wRegValue)
{
  _SetENDPOINT(bEpNum, wRegValue);
}

/*********************************************************************
 * @fn      GetENDPOINT
 *
 * @brief   Return the Endpoint register value.
 *
 * @param   bEpNum - Endpoint Number. 
 *
 * @return  Endpoint register value.
 */	
uint16_t GetENDPOINT(uint8_t bEpNum)
{
  return(_GetENDPOINT(bEpNum));
}

/*********************************************************************
 * @fn      SetEPType
 *
 * @brief   Set the Endpoint register value.
 *
 * @param   bEpNum - Endpoint Number. 
 *          wType - type definition.
 *
 * @return  none
 */	
void SetEPType(uint8_t bEpNum, uint16_t wType)
{
  _SetEPType(bEpNum, wType);
}

/*********************************************************************
 * @fn      GetEPType
 *
 * @brief   Returns the endpoint type.
 *
 * @param   bEpNum - Endpoint Number. 
 *
 * @return  Endpoint Type
 */	
uint16_t GetEPType(uint8_t bEpNum)
{
  return(_GetEPType(bEpNum));
}

/*********************************************************************
 * @fn      SetEPTxStatus
 *
 * @brief   Set the status of Tx endpoint.
 *
 * @param   bEpNum - Endpoint Number. 
 *          wState - new state.
 *
 * @return  none
 */	
void SetEPTxStatus(uint8_t bEpNum, uint16_t wState)
{
  _SetEPTxStatus(bEpNum, wState);
}

/*********************************************************************
 * @fn      SetEPRxStatus
 *
 * @brief   Set the status of Tx endpoint.
 *
 * @param   bEpNum - Endpoint Number. 
 *          wState - new state.
 *
 * @return  none
 */
void SetEPRxStatus(uint8_t bEpNum, uint16_t wState)
{
  _SetEPRxStatus(bEpNum, wState);
}

/*********************************************************************
 * @fn      SetDouBleBuffEPStall
 *
 * @brief   sets the status for Double Buffer Endpoint to STALL
 *
 * @param   bEpNum - Endpoint Number. 
 *          bDir - Endpoint direction.
 *
 * @return  none
 */
void SetDouBleBuffEPStall(uint8_t bEpNum, uint8_t bDir)
{
  uint16_t Endpoint_DTOG_Status;
	
  Endpoint_DTOG_Status = GetENDPOINT(bEpNum);
	
  if (bDir == EP_DBUF_OUT)
  { 
    _SetENDPOINT(bEpNum, Endpoint_DTOG_Status & ~EPRX_DTOG1);
  }
  else if (bDir == EP_DBUF_IN)
  { 
    _SetENDPOINT(bEpNum, Endpoint_DTOG_Status & ~EPTX_DTOG1);
  }
}

/*********************************************************************
 * @fn      GetEPTxStatus
 *
 * @brief   Returns the endpoint Tx status.
 *
 * @param   bEpNum - Endpoint Number. 
 *
 * @return  Endpoint TX Status
 */
uint16_t GetEPTxStatus(uint8_t bEpNum)
{
  return(_GetEPTxStatus(bEpNum));
}

/*********************************************************************
 * @fn      GetEPRxStatus
 *
 * @brief   Returns the endpoint Tx status.
 *
 * @param   bEpNum - Endpoint Number. 
 *
 * @return  Endpoint RX Status
 */
uint16_t GetEPRxStatus(uint8_t bEpNum)
{
  return(_GetEPRxStatus(bEpNum));
}

/*********************************************************************
 * @fn      SetEPTxValid
 *
 * @brief   Valid the endpoint Tx Status.
 *
 * @param   bEpNum - Endpoint Number. 
 *
 * @return  none
 */
void SetEPTxValid(uint8_t bEpNum)
{
  _SetEPTxStatus(bEpNum, EP_TX_VALID);
}

/*********************************************************************
 * @fn      SetEPRxValid
 *
 * @brief   Valid the endpoint Rx Status.
 *
 * @param   bEpNum - Endpoint Number. 
 *
 * @return  none
 */
void SetEPRxValid(uint8_t bEpNum)
{
  _SetEPRxStatus(bEpNum, EP_RX_VALID);
}

/*********************************************************************
 * @fn      SetEP_KIND
 *
 * @brief   Clear the EP_KIND bit.
 *
 * @param   bEpNum - Endpoint Number. 
 *
 * @return  none
 */
void SetEP_KIND(uint8_t bEpNum)
{
  _SetEP_KIND(bEpNum);
}

/*********************************************************************
 * @fn      ClearEP_KIND
 *
 * @brief   set the  EP_KIND bit.
 *
 * @param   bEpNum - Endpoint Number. 
 *
 * @return  none
 */
void ClearEP_KIND(uint8_t bEpNum)
{
  _ClearEP_KIND(bEpNum);
}

/*********************************************************************
 * @fn      Clear_Status_Out
 *
 * @brief   Clear the Status Out of the related Endpoint
 *
 * @param   bEpNum - Endpoint Number. 
 *
 * @return  none
 */
void Clear_Status_Out(uint8_t bEpNum)
{
  _ClearEP_KIND(bEpNum);
}

/*********************************************************************
 * @fn      Set_Status_Out
 *
 * @brief   Set the Status Out of the related Endpoint
 *
 * @param   bEpNum - Endpoint Number. 
 *
 * @return  none
 */
void Set_Status_Out(uint8_t bEpNum)
{
  _SetEP_KIND(bEpNum);
}

/*********************************************************************
 * @fn      SetEPDoubleBuff
 *
 * @brief   Enable the double buffer feature for the endpoint. 
 *
 * @param   bEpNum - Endpoint Number. 
 *
 * @return  none
 */
void SetEPDoubleBuff(uint8_t bEpNum)
{
  _SetEP_KIND(bEpNum);
}

/*********************************************************************
 * @fn      ClearEPDoubleBuff
 *
 * @brief   Disable the double buffer feature for the endpoint. 
 *
 * @param   bEpNum - Endpoint Number. 
 *
 * @return  none
 */
void ClearEPDoubleBuff(uint8_t bEpNum)
{
  _ClearEP_KIND(bEpNum);
}

/*********************************************************************
 * @fn      GetTxStallStatus
 *
 * @brief   Returns the Stall status of the Tx endpoint.
 *
 * @param   bEpNum - Endpoint Number. 
 *
 * @return  none
 */
uint16_t GetTxStallStatus(uint8_t bEpNum)
{
  return(_GetTxStallStatus(bEpNum));
}

/*********************************************************************
 * @fn      GetRxStallStatus
 *
 * @brief   Returns the Stall status of the Rx endpoint.
 *
 * @param   bEpNum - Endpoint Number. 
 *
 * @return  Rx Stall status.
 */
uint16_t GetRxStallStatus(uint8_t bEpNum)
{
  return(_GetRxStallStatus(bEpNum));
}

/*********************************************************************
 * @fn      ClearEP_CTR_RX
 *
 * @brief   Clear the CTR_RX bit.
 *
 * @param   bEpNum - Endpoint Number. 
 *
 * @return  none
 */
void ClearEP_CTR_RX(uint8_t bEpNum)
{
  _ClearEP_CTR_RX(bEpNum);
}

/*********************************************************************
 * @fn      ClearEP_CTR_TX
 *
 * @brief   Clear the CTR_TX bit.
 *
 * @param   bEpNum - Endpoint Number. 
 *
 * @return  none
 */
void ClearEP_CTR_TX(uint8_t bEpNum)
{
  _ClearEP_CTR_TX(bEpNum);
}

/*********************************************************************
 * @fn      ToggleDTOG_RX
 *
 * @brief   Toggle the DTOG_RX bit.
 *
 * @param   bEpNum - Endpoint Number. 
 *
 * @return  none
 */
void ToggleDTOG_RX(uint8_t bEpNum)
{
  _ToggleDTOG_RX(bEpNum);
}

/*********************************************************************
 * @fn      ToggleDTOG_TX
 *
 * @brief   Toggle the DTOG_TX bit.
 *
 * @param   bEpNum - Endpoint Number. 
 *
 * @return  none
 */
void ToggleDTOG_TX(uint8_t bEpNum)
{
  _ToggleDTOG_TX(bEpNum);
}

/*********************************************************************
 * @fn      ClearDTOG_RX.
 *
 * @brief   Clear the DTOG_RX bit.
 *
 * @param   bEpNum - Endpoint Number. 
 *
 * @return  none
 */
void ClearDTOG_RX(uint8_t bEpNum)
{
  _ClearDTOG_RX(bEpNum);
}

/*********************************************************************
 * @fn      ClearDTOG_TX.
 *
 * @brief   Clear the DTOG_TX bit.
 *
 * @param   bEpNum - Endpoint Number. 
 *
 * @return  none
 */
void ClearDTOG_TX(uint8_t bEpNum)
{
  _ClearDTOG_TX(bEpNum);
}

/*********************************************************************
 * @fn      SetEPAddress
 *
 * @brief   Set the endpoint address.
 *
 * @param   bEpNum - Endpoint Number. 
 *          bAddr - New endpoint address.
 *
 * @return  none
 */
void SetEPAddress(uint8_t bEpNum, uint8_t bAddr)
{
  _SetEPAddress(bEpNum, bAddr);
}

/*********************************************************************
 * @fn      GetEPAddress
 *
 * @brief   Clear the DTOG_TX bit.
 *
 * @param   bEpNum - Endpoint Number. 
 *
 * @return  Endpoint address.
 */
uint8_t GetEPAddress(uint8_t bEpNum)
{
  return(_GetEPAddress(bEpNum));
}

/*********************************************************************
 * @fn      SetEPTxAddr
 *
 * @brief   Set the endpoint Tx buffer address.
 *
 * @param   bEpNum - Endpoint Number. 
 *          bAddr - New endpoint address.
 *
 * @return  none
 */
void SetEPTxAddr(uint8_t bEpNum, uint16_t wAddr)
{
  _SetEPTxAddr(bEpNum, wAddr);
}

/*********************************************************************
 * @fn      SetEPRxAddr
 *
 * @brief   Set the endpoint Rx buffer address.
 *
 * @param   bEpNum - Endpoint Number. 
 *          bAddr - New endpoint address.
 *
 * @return  none
 */
void SetEPRxAddr(uint8_t bEpNum, uint16_t wAddr)
{
  _SetEPRxAddr(bEpNum, wAddr);
}

/*********************************************************************
 * @fn      GetEPTxAddr
 *
 * @brief   Returns the endpoint Tx buffer address.
 *
 * @param   bEpNum - Endpoint Number. 
 *
 * @return  Rx buffer address. 
 */
uint16_t GetEPTxAddr(uint8_t bEpNum)
{
  return(_GetEPTxAddr(bEpNum));
}

/*********************************************************************
 * @fn      GetEPRxAddr.
 *
 * @brief   Returns the endpoint Rx buffer address.
 *
 * @param   bEpNum - Endpoint Number. 
 *
 * @return  Rx buffer address. 
 */
uint16_t GetEPRxAddr(uint8_t bEpNum)
{
  return(_GetEPRxAddr(bEpNum));
}

/*********************************************************************
 * @fn      SetEPTxCount.
 *
 * @brief   Set the Tx count.
 *
 * @param   bEpNum - Endpoint Number. 
 *          wCount - new count value.
 *
 * @return  none
 */
void SetEPTxCount(uint8_t bEpNum, uint16_t wCount)
{
  _SetEPTxCount(bEpNum, wCount);
}

/*********************************************************************
 * @fn      SetEPCountRxReg.
 *
 * @brief   Set the Count Rx Register value.
 *
 * @param   *pdwReg - Endpoint Number. 
 *          wCount - new count value.
 *
 * @return  none
 */
void SetEPCountRxReg(uint32_t *pdwReg, uint16_t wCount)
{
  _SetEPCountRxReg(dwReg, wCount);
}

/*********************************************************************
 * @fn      SetEPTxCount.
 *
 * @brief   Set the Tx count.
 *
 * @param   bEpNum - Endpoint Number. 
 *          wCount - new count value.
 *
 * @return  none
 */
void SetEPRxCount(uint8_t bEpNum, uint16_t wCount)
{
  _SetEPRxCount(bEpNum, wCount);
}

/*********************************************************************
 * @fn      GetEPTxCount
 *
 * @brief   Get the Tx count.
 *
 * @param   bEpNum - Endpoint Number. 
 *
 * @return  Tx count value.
 */
uint16_t GetEPTxCount(uint8_t bEpNum)
{
  return(_GetEPTxCount(bEpNum));
}
/*********************************************************************
 * @fn      GetEPRxCount
 *
 * @brief   Get the Rx count.
 *
 * @param   bEpNum - Endpoint Number. 
 *
 * @return  Rx count value.
 */
uint16_t GetEPRxCount(uint8_t bEpNum)
{
  return(_GetEPRxCount(bEpNum));
}

/*********************************************************************
 * @fn      SetEPDblBuffAddr
 *
 * @brief   Set the addresses of the buffer 0 and 1.
 *
 * @param   bEpNum - Endpoint Number.
 *          wBuf0Addr - new address of buffer 0. 
 *          wBuf1Addr - new address of buffer 1.
 *
 * @return  none
 */
void SetEPDblBuffAddr(uint8_t bEpNum, uint16_t wBuf0Addr, uint16_t wBuf1Addr)
{
  _SetEPDblBuffAddr(bEpNum, wBuf0Addr, wBuf1Addr);
}

/*********************************************************************
 * @fn      SetEPDblBuf0Addr
 *
 * @brief   Set the Buffer 1 address.
 *
 * @param   bEpNum - Endpoint Number.
 *          wBuf0Addr - new address.
 *
 * @return  none
 */
void SetEPDblBuf0Addr(uint8_t bEpNum, uint16_t wBuf0Addr)
{
  _SetEPDblBuf0Addr(bEpNum, wBuf0Addr);
}

/*********************************************************************
 * @fn      SetEPDblBuf1Addr
 *
 * @brief   Set the Buffer 1 address.
 *
 * @param   bEpNum - Endpoint Number.
 *          wBuf1Addr - new address.
 *
 * @return  none
 */
void SetEPDblBuf1Addr(uint8_t bEpNum, uint16_t wBuf1Addr)
{
  _SetEPDblBuf1Addr(bEpNum, wBuf1Addr);
}

/*********************************************************************
 * @fn      GetEPDblBuf0Addr
 *
 * @brief   Returns the address of the Buffer 0.
 *
 * @param   bEpNum - Endpoint Number.
 *
 * @return  none
 */
uint16_t GetEPDblBuf0Addr(uint8_t bEpNum)
{
  return(_GetEPDblBuf0Addr(bEpNum));
}

/*********************************************************************
 * @fn      GetEPDblBuf1Addr
 *
 * @brief   Returns the address of the Buffer 1.
 *
 * @param   bEpNum - Endpoint Number.
 *
 * @return  Address of the Buffer 1.
 */
uint16_t GetEPDblBuf1Addr(uint8_t bEpNum)
{
  return(_GetEPDblBuf1Addr(bEpNum));
}

/*********************************************************************
 * @fn      SetEPDblBuffCount
 *
 * @brief   Set the number of bytes for a double Buffer endpoint. 
 *
 * @param   bEpNum,bDir, wCount
 *
 * @return  none
 */
void SetEPDblBuffCount(uint8_t bEpNum, uint8_t bDir, uint16_t wCount)
{
  _SetEPDblBuffCount(bEpNum, bDir, wCount);
}

/*********************************************************************
 * @fn      SetEPDblBuf0Count
 *
 * @brief   Set the number of bytes for a double Buffer endpoint. 
 *
 * @param   bEpNum,bDir, wCount
 *
 * @return  none
 */
void SetEPDblBuf0Count(uint8_t bEpNum, uint8_t bDir, uint16_t wCount)
{
  _SetEPDblBuf0Count(bEpNum, bDir, wCount);
}

/*********************************************************************
 * @fn      SetEPDblBuf1Count
 *
 * @brief   Set the number of bytes for a double Buffer endpoint. 
 *
 * @param   bEpNum,bDir, wCount
 *
 * @return  none
 */
void SetEPDblBuf1Count(uint8_t bEpNum, uint8_t bDir, uint16_t wCount)
{
  _SetEPDblBuf1Count(bEpNum, bDir, wCount);
}

/*********************************************************************
 * @fn      GetEPDblBuf0Count
 *
 * @brief   Returns the number of byte received in the buffer 0 of a double 
 *           Buffer endpoint.
 *
 * @param   bEpNum - Endpoint Number.
 *
 * @return  Endpoint Buffer 0 count
 */
uint16_t GetEPDblBuf0Count(uint8_t bEpNum)
{
  return(_GetEPDblBuf0Count(bEpNum));
}

/*********************************************************************
 * @fn      GetEPDblBuf1Count
 *
 * @brief   Returns the number of byte received in the buffer 1 of a double 
 *           Buffer endpoint.
 *
 * @param   bEpNum - Endpoint Number.
 *
 * @return  Endpoint Buffer 1 count
 */
uint16_t GetEPDblBuf1Count(uint8_t bEpNum)
{
  return(_GetEPDblBuf1Count(bEpNum));
}

/*********************************************************************
 * @fn      GetEPDblBufDir
 *
 * @brief   gets direction of the double buffered endpoint
 *
 * @param   bEpNum - Endpoint Number.
 *
 * @return  EP_DBUF_OUT, EP_DBUF_IN,
 *          EP_DBUF_ERR if the endpoint counter not yet programmed.
 */
EP_DBUF_DIR GetEPDblBufDir(uint8_t bEpNum)
{
  if ((uint16_t)(*_pEPRxCount(bEpNum) & 0xFC00) != 0)
    return(EP_DBUF_OUT);
  else if (((uint16_t)(*_pEPTxCount(bEpNum)) & 0x03FF) != 0)
    return(EP_DBUF_IN);
  else
    return(EP_DBUF_ERR);
}

/*********************************************************************
 * @fn      FreeUserBuffer
 *
 * @brief   free buffer used from the application realizing it to the line
 *          toggles bit SW_BUF in the double buffered endpoint register
 *
 * @param   bEpNum, bDir
 *
 * @return  none
 */
void FreeUserBuffer(uint8_t bEpNum, uint8_t bDir)
{
  if (bDir == EP_DBUF_OUT)
  {
    _ToggleDTOG_TX(bEpNum);
  }
  else if (bDir == EP_DBUF_IN)
  { 
    _ToggleDTOG_RX(bEpNum);
  }
}

/*********************************************************************
 * @fn      ToWord
 *
 * @brief   merge two byte in a word.
 *
 * @param   bh - byte high, bl - bytes low.
 *
 * @return  resulted word
 */
uint16_t ToWord(uint8_t bh, uint8_t bl)
{
  uint16_t wRet;
  wRet = (uint16_t)bl | ((uint16_t)bh << 8);
	
  return(wRet);
}

/*********************************************************************
 * @fn      ByteSwap
 *
 * @brief   Swap two byte in a word.
 *
 * @param   wSwW - word to Swap
 *
 * @return  resulted word
 */
uint16_t ByteSwap(uint16_t wSwW)
{
  uint8_t bTemp;
  uint16_t wRet;
  bTemp = (uint8_t)(wSwW & 0xff);
  wRet =  (wSwW >> 8) | ((uint16_t)bTemp << 8);
	
  return(wRet);
}
