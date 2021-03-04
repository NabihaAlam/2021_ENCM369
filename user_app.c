/*!*********************************************************************************************************************
@file user_app.c                                                                
@brief User's tasks / applications are written here.  This description
should be replaced by something specific to the task.

------------------------------------------------------------------------------------------------------------------------
GLOBALS
- NONE

CONSTANTS
- NONE

TYPES
- NONE

PUBLIC FUNCTIONS
- NONE

PROTECTED FUNCTIONS
- void UserApp1Initialize(void)
- void UserApp1Run(void)


**********************************************************************************************************************/

#include "configuration.h"

/***********************************************************************************************************************
Global variable definitions with scope across entire project.
All Global variable names shall start with "G_<type>UserApp1"
***********************************************************************************************************************/
/* New variables */
volatile u8 G_u8UserAppFlags;                             /*!< @brief Global state flags */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Existing variables (defined in other files -- should all contain the "extern" keyword) */
extern volatile u32 G_u32SystemTime1ms;                   /*!< @brief From main.c */
extern volatile u32 G_u32SystemTime1s;                    /*!< @brief From main.c */
extern volatile u32 G_u32SystemFlags;                     /*!< @brief From main.c */


/***********************************************************************************************************************
Global variable definitions with scope limited to this local application.
Variable names shall start with "UserApp_<type>" and be declared as static.
***********************************************************************************************************************/


/**********************************************************************************************************************
Function Definitions
**********************************************************************************************************************/

/*--------------------------------------------------------------------------------------------------------------------*/
/*! @publicsection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
/*! @protectedsection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------------------------------------------------
@fn void UserAppInitialize(void)

@brief
Initializes the application's variables.

Should only be called once in main init section.

Requires:
- NONE

Promises:
- NONE

*/
void UserAppInitialize(void)
{
    LATA = 0x81;  //Initialize LED
    T0CON0 = 0x90; //Enable, 16-bit, postscaler
    T0CON1 = 0x54; //Set clock source, asynchronous, prescaler

} /* end UserAppInitialize() */

  
/*!----------------------------------------------------------------------------------------------------------------------
@fn void UserAppRun(void)

@brief Application code that runs once per system loop

Requires:
- 

Promises:
- 

*/
void UserAppRun(void)
{
    static u16 u16TimerCounter = 0;             
    static u8 u8CurrentState = 0;                     
    static u8 u8Direction = 0; //to change the direction (making it bounce back and forth))
    
    u8 u8LedState[] = {0x01,0x02,0x04,0x08,0x10,0x20};   //pattern
    u16 u16LataState = 0x80&LATA;  // bitmasking masking by making 6LSB low           
    
    if(u16TimerCounter==200 && u8Direction == 0)//count forward and write to LATA every 200ms
    {
        LATA = u16LataState|u8LedState[u8CurrentState];
        u8CurrentState++;
        if(u8CurrentState==5)//if it comes to the end of the pattern
        {
            u8Direction = 1; //change direction in an increasing manner
        }
        u16TimerCounter=0;
    }
    if(u16TimerCounter==200 && u8Direction ==1)//count backward and write to LATA every 200ms
    {
        LATA = u16LataState|u8LedState[u8CurrentState];
        u8CurrentState--;
        if(u8CurrentState==0)
        {
            u8Direction = 0; //change direction in an decreasing manner
        }
        u16TimerCounter=0;
    }
    
    u16TimerCounter++; //increment counter each time through userapp/ ~1ms

} /* end UserAppRun */



/*------------------------------------------------------------------------------------------------------------------*/
/*! @privatesection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/





/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
