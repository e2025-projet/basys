/*******************************************************************************
  MPLAB Harmony Application Source File
  
  Company:
    Microchip Technology Inc.
  
  File Name:
    main.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It 
    implements the logic of the application's state machine and it may call 
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013-2014 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
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
// DOM-IGNORE-END


// *****************************************************************************
// *****************************************************************************
// Section: Included Files 
// *****************************************************************************
// *****************************************************************************

#include "main.h"
#include "system_config.h"
#include "system/common/sys_module.h"   // SYS function prototypes
#include "driver/spi/src/dynamic/drv_spi_internal.h"
#include "UDP_app.h"
#include "led.h"
#include "rgbled.h"
#include "ssd.h"
#include "I2S.h"
#include "accel.h"
#include "lcd.h"
#include "adc.h"
#include "gain_out.h"
#include "app_commands.h"
#include "fsm.h"


//Moyenne est faite direct sur la MX3 (GestionMoyenne dans accel.c)
//La switch qui fait afficher Moyenne sur le LCD dans accel.C



// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the TCPIP_Initialize function.
    
    Application strings and buffers are be defined outside this structure.
 */

MAIN_DATA mainData;

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

/* TODO:  Add any necessary callback functions.
 */

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************

int Intense[3];
int Last_Intense[3];

void Interupt_ACL_Init(void)
{
    IFS0bits.INT4IF = 0;
    IEC0bits.INT4IE = 1;
    IPC4bits.INT4IP = 1;
    IPC4bits.INT4IS = 0;
    INTCONbits.INT4EP = 0;
    INT4Rbits.INT4R = 12;    //assigner le Interupt au boutton C en mettant 4, quand ca va �tre ok mettre 12
}

static bool sw0_old; 
void ManageSwitches()
{
    bool sw0_new = SWITCH0StateGet();
    if((sw0_new != sw0_old) && sw0_new)
    {
        strcpy(UDP_Send_Buffer, "Bonjour S4\n\r");
        UDP_bytes_to_send = strlen(UDP_Send_Buffer);
        UDP_Send_Packet = true;       
    }

    sw0_old = sw0_new; 
}

void RGB_Task()
{
    //if(timer_1m) {               // Interruption � chaque 1 ms
        //timer_1m = 0;            // Reset the compteur to capture the next event
        //Toute pour la Moyenne fait directement dans la MX3 avec la fonction GestionMoyenne dans accel.c
        Intense[0] = (MoyenneX*255)/2096;
        Intense[1] = (MoyenneY*255)/2096;
        Intense[2] = (MoyenneZ*255)/2096;

        if(Intense[0] <= 0)
        {
            Intense[0] = Last_Intense[0];
        }
        else
        {
          Last_Intense[0] = Intense[0];  
        }

        if(Intense[1] <= 0)
        {
            Intense[1] = Last_Intense[1];
        }
        else
        {
          Last_Intense[0] = Intense[0];  
        }

        if(Intense[2] <= 0)
        {
            Intense[2] = Last_Intense[2];
        }
        else
        {
          Last_Intense[0] = Intense[0];  
        }

        RGBLED_SetValue(Intense[0], Intense[1], Intense[2]); 
    //}
}


// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void MAIN_Initialize ( void )

  Remarks:
    See prototype in main.h.
 */

void MAIN_Initialize ( void )
{
     
    /* Place the App state machine in its initial state. */
    mainData.state = MAIN_STATE_INIT;
    mainData.handleUSART0 = DRV_HANDLE_INVALID;
        uint8_t dist_sensor_en = 0;
        
    OC1_Init();         // Set up Output Compare
    Timer3_Init();      // Required for OC1
    SPI1_I2S_Config();  // SPI2 in I�S mode
    UDP_Initialize(); // Initialisation de du serveur et client UDP
    LCD_Init(); // Initialisation de l'�cran LCD
    
    T4CONbits.ON = 0;// turn off Timer1
    // turn off digits
    lat_SSD_AN1 = 1; // deactivate digit 1;
    lat_SSD_AN2 = 1; // deactivate digit 2;    
    lat_SSD_AN3 = 1; // deactivate digit 3;   
    lat_SSD_AN0 = 1; // deactivate digit 0;
    
//    ACL_Init(); // Initialisation de l'acc�l�rom�tre
//    SSD_Init(); // Initialisation du Timer4 et de l'acc�l�rom�tre
//    Interupt_ACL_Init(); //Initialisation de l'interuption de l'acc�l�rom�tre
//    RGBLED_Init();
    
    LED_Init(); // Initialisation des LEDs
//    Initialize_ADC_Microphone(); 
    initDistSensor(dist_sensor_en, DEFAULT_AMB_TEMP);
    macro_enable_interrupts();
    
}


/******************************************************************************
  Function:
    void MAIN_Tasks ( void )
 * Fonction qui execute les t�ches de l'application. Cette fonction est une
 * machien d'�tat :
 * 1. MAIN_STATE_INIT; Initialise les p�riph�rique de communication USART et 
 *    passe � l'�tat 2 quand l'initialisation est termin�e.
 * 2. MAIN_STATE_SERVICE_TASKS; Execute les t�ches de l'application. Ne change 
 * jamais d'�tat.

  Remarks:
    See prototype in main.h.
 */

void MAIN_Tasks ( void )
{

    /* Check the application's current state. */
    switch ( mainData.state )
    {
            /* Application's initial state. */
        case MAIN_STATE_INIT:
        {
            bool appInitialized = true;
            SYS_CONSOLE_MESSAGE("Init\r\n");

            if (mainData.handleUSART0 == DRV_HANDLE_INVALID)
            {
                mainData.handleUSART0 = DRV_USART_Open(MAIN_DRV_USART, DRV_IO_INTENT_READWRITE|DRV_IO_INTENT_NONBLOCKING);
                appInitialized &= (DRV_HANDLE_INVALID != mainData.handleUSART0);
            }


            if (appInitialized)
            {
                mainData.state = MAIN_STATE_SERVICE_TASKS;
            }
            break;
        }

        case MAIN_STATE_SERVICE_TASKS:
        {
            RGB_Task();
            UDP_Tasks();
            ManageSwitches();
            updateState();
        	JB1Toggle();
            break;
        }

            /* The default state should never be executed. */
        default:
        {
            /* TODO: Handle error in application's state machine. */
            break;
        }
    }
}



int main(void) {
    SYS_Initialize(NULL);
    MAIN_Initialize();
    SYS_INT_Enable();
    SSD_Close();
//    LCD_WriteStringAtPos("Projet S4: ANC", 1, 0);
    
    while (1) {
        SYS_Tasks();
        MAIN_Tasks();
    };

    return 0;
}


/*******************************************************************************
 End of File
 */
