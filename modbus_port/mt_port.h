/**
  ******************************************************************************
  * @file           : mt_port.h
  * @brief          : Additional porting data
  * @author         : MicroTechnics (microtechnics.ru)
  ******************************************************************************
  */

#ifndef MT_PORT_H
#define MT_PORT_H



/* Includes ------------------------------------------------------------------*/

#include "at32f403a_407_wk_config.h"



/* Declarations and definitions ----------------------------------------------*/




/* Functions -----------------------------------------------------------------*/

void MT_PORT_SetTimerModule(tmr_type* timer);
void MT_PORT_SetUartModule(usart_type* uart);



#endif // #ifndef MT_PORT_H
