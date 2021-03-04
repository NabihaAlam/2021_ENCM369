/*!**********************************************************************************************************************
@file encm369_pic18.c                                                                
@brief This file provides core and GPIO functions for the ENCM 369 PIC activities.


------------------------------------------------------------------------------------------------------------------------
GLOBALS
- NONE

CONSTANTS
- NONE

TYPES
- NONE

PUBLIC FUNCTIONS
- 

PROTECTED FUNCTIONS
- 

***********************************************************************************************************************/

#include "configuration.h"

/***********************************************************************************************************************
Global variable definitions with scope across entire project.
All Global variable names shall start with "G_xxBsp"
***********************************************************************************************************************/
/* New variables */




/*--------------------------------------------------------------------------------------------------------------------*/
/* Existing variables (defined in other files -- should all contain the "extern" keyword) */
extern volatile u32 G_u32SystemTime1ms;        /*!< @brief From main.c */
extern volatile u32 G_u32SystemTime1s;         /*!< @brief From main.c */
extern volatile u32 G_u32SystemFlags;          /*!< @brief From main.c */

/***********************************************************************************************************************
Global variable definitions with scope limited to this local application.
Variable names shall start with "Bsp_" and be declared as static.
***********************************************************************************************************************/

/***********************************************************************************************************************
Function Definitions
***********************************************************************************************************************/


/*--------------------------------------------------------------------------------------------------------------------*/
/*! @protectedsection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/



/*!---------------------------------------------------------------------------------------------------------------------
@fn void ClockSetup(void)

@brief Loads all registers required to set up the processor clocks.

Requires:
- NONE

Promises:
- EFC is set up with proper flash access wait states based on 48MHz system clock
- PMC is set up with proper oscillators and clock sources

*/
void ClockSetup(void)
{
 
  
} /* end ClockSetup */


/*!---------------------------------------------------------------------------------------------------------------------
@fn void GpioSetup(void)

@brief Loads registers required to set up GPIO on the processor.

Requires:
- All configurations must match connected hardware.

Promises:
- Output pin for PA31_HEARTBEAT is configured

*/
void GpioSetup(void)
{
    TRISA = 0x00;   //set LATA to outputs
    ANSELA = 0x00;  //set LATA to digital
    LATA = 0x80;    //set RA7 and RA0 on, the rest off
    
    TRISB = 0xFF;   //set PORTB to all inputs (only care about RA5/RA4)
    ANSELB = 0x00;  //set PORTB to digital
    
} /* end GpioSetup() */


/*!---------------------------------------------------------------------------------------------------------------------
@fn  void SysTickSetup(void)

@brief Initializes the 1ms and 1s System Ticks off the core timer.

Requires:
- NVIC is setup and SysTick handler is installed

Promises:
- Both global system timers are reset and the SysTick core timer is configured for 1ms intervals

*/
void SysTickSetup(void)
{
  G_u32SystemTime1ms = 0;      
  G_u32SystemTime1s  = 0;   
  
} /* end SysTickSetup() */



/*!---------------------------------------------------------------------------------------------------------------------
@fn void SystemSleep(void)

@brief Puts the system into sleep mode.  


Requires:
- 
 * 
Promises:
- 

*/
void SystemSleep(void)
{    
  
} /* end SystemSleep(void) */



/*!---------------------------------------------------------------------------------------------------------------------
@fn void TimeXus(u16 u16Microseconds)

@brief Sets Timer0 to count u16Microseconds 


Requires:
- Timer0 configured such that each timer tick is 1 microseconds
- u16Microseconds is the value in microseconds to time from 1 to 65,535
 * 
Promises:
- Pre-loads TMR0H:L to clock out desired period
- TMROIF cleared
- Timer0 enabled
*/
void TimeXus(u16 u16Microseconds)
{    
    T0CON0 = T0CON0 & 0x7F;   // Timer0 Enable low
    
    u16 u16OverFlowCounter = 0xFFFF - u16Microseconds;  //time left before overflow
    
    u8 u8InputL = u16OverFlowCounter & 0xFF;   //bitmask 8 LSBs
    u8 u8InputH = (u16OverFlowCounter >> 8) & 0xFF;  //bitmask 8 MSBs
    TMR0L = u8InputL;  //preload Timer0 8 LSBs
    TMR0H = u8InputH; //preload Timer0 8 MSBs
    
    PIR3 = PIR3 & 0x7F;  //sets TMR0IF low
    
    T0CON0 = T0CON0 | 0x80;  //sets Timer0 Enable high
      
} /* end TimeXus(u16 u16Microseconds) */



/*--------------------------------------------------------------------------------------------------------------------*/
/*! @publicsection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/



/*--------------------------------------------------------------------------------------------------------------------*/
/*! @privatesection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File */
/*--------------------------------------------------------------------------------------------------------------------*/



