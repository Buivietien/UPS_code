/*******************************************************************************
  Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This file contains the "main" function for a project.

  Description:
    This file contains the "main" function for a project.  The
    "main" function calls the "SYS_Initialize" function to initialize the state
    machines of all modules in the system
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
// #include <stdio.h>                      // Defines StandardIO functions
#include "definitions.h"   
// #include <../src/gcode_parser/GCodeParser.c> 
#include <gcode_parser/GCodeParser.h> 
#include <inverter_control/inverter.h>
#include <system_mornitor_n_leds/system_mornitor.h>
#include <printf_custom/printf.h>
      


// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

extern int GcodeParser_lineCharCount;
extern char GcodeParser_line[GCODEPARSER_MAX_LINE_SIZE + 2];
extern char* GcodeParser_comments;
extern char* GcodeParser_lastComment;
extern bool GcodeParser_blockDelete;
extern bool GcodeParser_beginEnd;
extern bool GcodeParser_completeLineIsAvailableToParse;

int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );
    SYSTICK_TimerStart();
    
    inv_spwm_init();
    push_pull_ctrl_init();
    adc_init();
    system_mornitor_init(); //Init the system mornitor ISR
    custom_uart_init();
    GcodeParser_Initialize();

    printf("Initialize SERCOM1 completed\n");
    while ( true )
    {      
      //Read all serial input
      for(int i = 0; i < SERCOM1_USART_ReadCountGet(); i++){
        char temp_serial = 0;
        SERCOM1_USART_Read(&temp_serial, 1); //Only read 1 byte
        bool status = GcodeParser_AddCharToLine(temp_serial); 
      }
      if (GcodeParser_completeLineIsAvailableToParse == true){
          printf(GcodeParser_line); printf("\n");  
          GcodeParser_Execute();          
      }





        
//        SYSTICK_DelayMs(500);       
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

