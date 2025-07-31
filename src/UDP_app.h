/*******************************************************************************
  MPLAB Harmony Application Header File

  Company:
    Microchip Technology Inc.

  File Name:
    app.h

  Summary:
    This header file provides prototypes and definitions for the application.

  Description:
    This header file provides function prototypes and data type definitions for
    the application.  Some of these are required by the system (such as the
    "UDP_Initialize" and "UDP_Tasks" prototypes) and some of them are only used
    internally by the application (such as the "UDP_STATES" definition).  Both
    are defined here for convenience.
*******************************************************************************/


#ifndef _UDP_H
#define _UDP_H


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "system_config.h"
#include "system_definitions.h"

// *****************************************************************************
// *****************************************************************************
// Section: Type Definitions
// *****************************************************************************
// *****************************************************************************

typedef enum
{
    UDP_TCPIP_WAIT_INIT,

    /* In this state, the application waits for a IP Address */
    UDP_TCPIP_WAIT_FOR_IP,

    UDP_TCPIP_OPENING_SERVER,
    UDP_TCPIP_WAITING_FOR_COMMAND,

    UDP_TCPIP_WAIT_ON_DNS,

    UDP_TCPIP_WAIT_FOR_CONNECTION,

    UDP_TCPIP_SERVING_CONNECTION,
    UDP_TCPIP_WAIT_FOR_RESPONSE,

    UDP_TCPIP_CLOSING_CONNECTION,

    UDP_TCPIP_ERROR,
} UDP_STATES;

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    Application strings and buffers are be defined outside this structure.
 */

typedef struct
{
    /* The application's current state */
    UDP_STATES              clientState;
    UDP_STATES              serverState;

    /* TODO: Define any additional data used by the application. */
    UDP_SOCKET              serverSocket;
    UDP_SOCKET              clientSocket;

    uint64_t    mTimeOut;

} UDP_DATA;



// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Routines
// *****************************************************************************
// *****************************************************************************
/* These routines are called by drivers when certain events occur.
*/

	
// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void UDP_Initialize ( void )

  Summary:
     MPLAB Harmony application initialization routine.

  Description:
    This function initializes the Harmony application.  It places the 
    application in its initial state and prepares it to run so that its 
    UDP_Tasks function can be called.

  Precondition:
    All other system initialization routines should be called before calling
    this routine (in "SYS_Initialize").

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    UDP_Initialize();
    </code>

  Remarks:
    This routine must be called from the SYS_Initialize function.
*/

void UDP_Initialize ( void );


/*******************************************************************************
  Function:
    void UDP_Tasks ( void )

  Summary:
    MPLAB Harmony Demo application tasks function

  Description:
    This routine is the Harmony Demo application's tasks function.  It
    defines the application's state machine and core logic.

  Precondition:
    The system and application initialization ("SYS_Initialize") should be
    called before calling this.

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    UDP_Tasks();
    </code>

  Remarks:
    This routine must be called from SYS_Tasks() routine.
 */

void UDP_Tasks ( void );


#endif /* _UDP_H */
/*******************************************************************************
 End of File
 */

