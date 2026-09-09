/**
  ******************************************************************************
  * @file           : mt_port.c
  * @brief          : Additional porting data
  * @author         : MicroTechnics (microtechnics.ru)
  ******************************************************************************
  */



/* Includes ------------------------------------------------------------------*/

#include "mt_port.h"



/* Declarations and definitions ----------------------------------------------*/

static uint32_t lockCounter = 0;

usart_type* modbusUart =USART2;
tmr_type* modbusTimer = TMR3;



/* Functions -----------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
void EnterCriticalSection()
{
  __disable_irq();
  lockCounter++;
}



/*----------------------------------------------------------------------------*/
void ExitCriticalSection()
{
  lockCounter--;

  if (lockCounter == 0)
  {
    __enable_irq();
  }
}



/*----------------------------------------------------------------------------*/
void MT_PORT_SetTimerModule(tmr_type* timer)
{
  modbusTimer = timer;
}



/*----------------------------------------------------------------------------*/
void MT_PORT_SetUartModule(usart_type* uart)
{
  modbusUart = uart;
}



/*----------------------------------------------------------------------------*/
