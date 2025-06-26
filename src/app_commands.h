/*******************************************************************************
  Application Header

  File Name:
    app_commands.h

  Summary:
 code for the console commands for the simple tcp client demo

  Description:
    code for the console commands for the simple tcp client demo
 *******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2011-2012 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED AS IS WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 *******************************************************************************/
//DOM-IGNORE-END
#include <stdint.h>

#ifndef TCPIP_COMMANDS_H
#define	TCPIP_COMMANDS_H

#ifdef	__cplusplus
extern "C" {
#endif
#define MAX_URL_SIZE 255
bool TCPIP_Commands_Init();
extern char TCPIP_Hostname_Buffer[MAX_URL_SIZE];
extern char TCPIP_Port_Buffer[6];
extern char TCPIP_Message_Buffer[MAX_URL_SIZE];
extern bool TCPIP_Send_Packet;

#ifdef	__cplusplus
}
#endif

#endif	/* TCPIP_COMMANDS_H */

#ifndef UDP_COMMANDS_H
#define	UDP_COMMANDS_H

#ifdef	__cplusplus
extern "C" {
#endif
//#define MAX_URL_SIZE 255
#define MAX_PACKET_SIZE 1536
bool UDP_Commands_Init();
extern char UDP_Hostname_Buffer[MAX_URL_SIZE];
extern char UDP_Port_Buffer[6];
extern char UDP_Send_Buffer[MAX_PACKET_SIZE+1];
extern char UDP_Receive_Buffer[MAX_PACKET_SIZE+1];
extern uint8_t UDP_Server_Receive_Buffer[MAX_PACKET_SIZE+1];
extern bool UDP_Send_Packet;
extern bool UDP_Receive_Packet;
extern uint16_t UDP_bytes_to_send;
extern uint16_t UDP_bytes_received;


#ifdef	__cplusplus
}
#endif

#endif	/* TCPIP_COMMANDS_H */