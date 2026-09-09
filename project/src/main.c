/* add user code begin Header */
/**
  **************************************************************************
  * @file     main.c
  * @brief    main program
  **************************************************************************
  * Copyright (c) 2025, Artery Technology, All rights reserved.
  *
  * The software Board Support Package (BSP) that is made available to
  * download from Artery official website is the copyrighted work of Artery.
  * Artery authorizes customers to use, copy, and distribute the BSP
  * software and its related documentation for the purpose of design and
  * development in conjunction with Artery microcontrollers. Use of the
  * software is governed by this copyright notice and the following disclaimer.
  *
  * THIS SOFTWARE IS PROVIDED ON "AS IS" BASIS WITHOUT WARRANTIES,
  * GUARANTEES OR REPRESENTATIONS OF ANY KIND. ARTERY EXPRESSLY DISCLAIMS,
  * TO THE FULLEST EXTENT PERMITTED BY LAW, ALL EXPRESS, IMPLIED OR
  * STATUTORY OR OTHER WARRANTIES, GUARANTEES OR REPRESENTATIONS,
  * INCLUDING BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
  *
  **************************************************************************
  */
/* add user code end Header */

/* Includes ------------------------------------------------------------------*/
#include "at32f403a_407_wk_config.h"
#include "wk_debug.h"
#include "wk_tmr.h"
#include "wk_usart.h"
#include "wk_gpio.h"
#include "wk_system.h"

/* private includes ----------------------------------------------------------*/
/* add user code begin private includes */

#include "mbconfig.h"
#include "mb.h"
#include "mb_m.h"
#include "mbport.h"
#include "mt_port.h"

#include "mbtask.h"

/* add user code end private includes */

/* private typedef -----------------------------------------------------------*/
/* add user code begin private typedef */

/* add user code end private typedef */

/* private define ------------------------------------------------------------*/
/* add user code begin private define */

/* add user code end private define */

/* private macro -------------------------------------------------------------*/
/* add user code begin private macro */

/* add user code end private macro */

/* private variables ---------------------------------------------------------*/
/* add user code begin private variables */
USHORT usRegInputBuf[REG_INPUT_NREGS] = {0};
USHORT usRegHoldingBuf[REG_HOLDING_NREGS] = {0} ;
UCHAR  ucRegCoilsBuf[REG_COILS_SIZE / 8] = {0} ;
UCHAR  ucRegDiscreteBuf[REG_DISCRETE_SIZE / 8] = {0} ;
/* add user code end private variables */

/* private function prototypes --------------------------------------------*/
/* add user code begin function prototypes */

/* add user code end function prototypes */

/* private user code ---------------------------------------------------------*/
/* add user code begin 0 */

/* add user code end 0 */

/**
  * @brief main function.
  * @param  none
  * @retval none
  */
int main(void)
{
  /* add user code begin 1 */

  /* add user code end 1 */

  /* system clock config. */
  wk_system_clock_config();

  /* config periph clock. */
  wk_periph_clock_config();

  /* init debug function. */
  wk_debug_config();

  /* nvic config. */
  wk_nvic_config();

  /* timebase config for
     void wk_delay_ms(uint32_t delay); */
  wk_timebase_init();

  /* init gpio function. */
  wk_gpio_config();

  /* usart1 already supports printf. */
  /* init usart1 function. */
  wk_usart1_init();

  /* init usart2 function. */
  wk_usart2_init();

  /* init usart6 function. */
  wk_usart6_init();

  /* init tmr2 function. */
  wk_tmr2_init();

  /* init tmr3 function. */
  wk_tmr3_init();

  /* add user code begin 2 */
  //  MT_PORT_SetTimerModule(USART2);
  //  MT_PORT_SetUartModule(TMR3);
     printf("Start Modbus master\r\n");
   eMBErrorCode eStatus;
   eStatus = eMBMasterInit(MB_RTU, 0, 9600, MB_PAR_NONE);
   printf("Init Modbus master\r\n");
   eStatus = eMBMasterEnable();
   wk_delay_ms(500);
   printf("Modbus master enable\r\n");
   if (eStatus != MB_ENOERR)
   {
    printf("Modbus master error\r\n");
   // Error handling
   }
    /*modbus slave*/ 
    modbus_task(); 
  /* add user code end 2 */

  while(1)
  {
    /* add user code begin 3 */
    eMBMasterPoll();
    eMBMasterReqWriteHoldingRegister(0x01, 0x1, 0x2, 1000);
    wk_delay_ms(100);
    printf("Modbus master\r\n");
    /* add user code end 3 */
  }
}

  /* add user code begin 4 */
/*----------------------------------------------------------------------------*/
eMBErrorCode eMBMasterRegInputCB(UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs)
{
  eMBErrorCode eStatus = MB_ENOERR;
  return eStatus;
}
/*----------------------------------------------------------------------------*/
eMBErrorCode eMBMasterRegHoldingCB(UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs, eMBRegisterMode eMode)
{
  eMBErrorCode eStatus = MB_ENOERR;
  return eStatus;
}
/*----------------------------------------------------------------------------*/
eMBErrorCode eMBMasterRegCoilsCB(UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNCoils, eMBRegisterMode eMode)
{
  eMBErrorCode eStatus = MB_ENOERR;
  return eStatus;
}
/*----------------------------------------------------------------------------*/
eMBErrorCode eMBMasterRegDiscreteCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNDiscrete )
{
  eMBErrorCode eStatus = MB_ENOERR;
  return eStatus;
}

  /* add user code end 4 */
