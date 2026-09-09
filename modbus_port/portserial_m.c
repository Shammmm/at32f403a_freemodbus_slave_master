/*
 * FreeModbus Libary: BARE Port
 * Copyright (C) 2006 Christian Walter <wolti@sil.at>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * File: $Id$
 */

#include "port.h"

/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbport.h"
#include "at32f403a_407_wk_config.h"


/* ----------------------- static functions ---------------------------------*/
static void prvvUARTTxReadyISR(void);
static void prvvUARTRxISR(void);




/* ----------------------- Variables ----------------------------------------*/
extern usart_type* modbusUart;

// static uint8_t txByte = 0x00;
// static uint8_t rxByte = 0x00;



/* ----------------------- Start implementation -----------------------------*/

/*----------------------------------------------------------------------------*/
void vMBMasterPortSerialEnable(BOOL xRxEnable, BOOL xTxEnable)
{
   if(xRxEnable == TRUE)  
  {
    gpio_bits_reset(COM_TX_GPIO_PORT,  COM_TX_PIN );
    usart_interrupt_enable(modbusUart, USART_RDBF_INT, TRUE);

  }
  else
  {
    gpio_bits_set(COM_TX_GPIO_PORT,  COM_TX_PIN );
    usart_interrupt_enable(modbusUart, USART_RDBF_INT, FALSE);

  }

  if(xTxEnable == TRUE)
  {
    
    usart_interrupt_enable(modbusUart, USART_TDBE_INT, TRUE);


  }
  else
  {
    usart_interrupt_enable(modbusUart, USART_TDBE_INT, FALSE);

  }
}



/* --------------------------------------------------------------------------*/
BOOL xMBMasterPortSerialInit(UCHAR ucPORT, ULONG ulBaudRate, UCHAR ucDataBits, eMBParity eParity)
{
  return TRUE;
}



/* --------------------------------------------------------------------------*/
BOOL xMBMasterPortSerialPutByte(CHAR ucByte)
{
  usart_data_transmit(modbusUart, ucByte);
  return TRUE;
}



/* --------------------------------------------------------------------------*/
BOOL xMBMasterPortSerialGetByte( CHAR * pucByte )
{
  *pucByte = usart_data_receive(modbusUart);
  return TRUE;
}



/* --------------------------------------------------------------------------*/
static void prvvUARTTxReadyISR(void)
{
  pxMBMasterFrameCBTransmitterEmpty();
}



/* --------------------------------------------------------------------------*/
static void prvvUARTRxISR(void)
{
  pxMBMasterFrameCBByteReceived();
}



/* --------------------------------------------------------------------------*/
// void HAL_UART_TxCpltCallback(usart_type *huart)
// {
//   if (huart == modbusUart)
//   {
//     prvvUARTTxReadyISR();
//   }
// }



// /* --------------------------------------------------------------------------*/
// void HAL_UART_RxCpltCallback(usart_type *huart)
// {
//   if (huart == modbusUart)
//   {
//     prvvUARTRxISR();
//   }
// }

void vUSARTHandler_m( void )
{
    if(modbusUart->ctrl1_bit.rdbfien == SET)
    {
      if(usart_flag_get(modbusUart, USART_RDBF_FLAG) == SET)
      {

        prvvUARTRxISR();
      }
    }
    
    if(modbusUart->ctrl1_bit.tdbeien == SET)
    {
      if(usart_flag_get(modbusUart, USART_TDC_FLAG) == SET)
      {
       
        prvvUARTTxReadyISR();
      }
    }
}

/* --------------------------------------------------------------------------*/
