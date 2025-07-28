/* 
 * Auteur : JG et OP
 * Fichier : analogdc.c
 */

/* Microchip includes */
#include <xc.h>
#include <sys/attribs.h>

/* Basys MX3 includes */
#include "config.h"

/* APP3 includes*/
#include "analogdc.h"

#include <xc.h>
#include <sys/attribs.h>
#include "system_definitions.h"
#include <stdio.h>
#include "lcd.h"
#include "ssd.h"
#include "app_commands.h"

 unsigned char ADC_Send[ADC_LEN];
 volatile int adc_ptr;
 volatile uint8_t adc_ready;
 uint32_t sum;
 char charSum[12];
 const char audio_header[6] = {'A', 'U', 'D', 'I', 'O', ' '};
 
void send_adc_val(void) {
    // Channel select
    if (adc_ready) {
        int i = 0;
        sum = 0;
        for (i = 0; i < ADC_LEN; i++ ) {
            sum += (uint8_t)ADC_Send[i];
        }
        
        sprintf(charSum, "%lu", sum);
        //SYS_CONSOLE_PRINT("Sum of data : %s \r\n", sum);
        //strcpy(UDP_Send_Buffer, audio_header);
        strcpy(UDP_Send_Buffer, ADC_Send);
        //UDP_bytes_to_send = strlen(ADC_Send);
        UDP_Send_Packet = true;
        adc_ready = 0;
    }
}

// Config @ 8kHz

void init_timer3(void)
{
    T3CON = 0;
    T3CONbits.TCKPS = 0b000;      // Prédiviseur 1:1
    PR3             = 59999;        // Valeur pour PR2 (767 - 62.5 kHz PWM base)
    TMR3            = 0;
    
    IPC3bits.T3IP   = 1;          // Priorité d'interruption
    IPC3bits.T3IS   = 0;
    IFS0bits.T3IF   = 0;          // Efface flag
    IEC0bits.T3IE   = 1;          // Active ISR Timer2
    
    T3CONbits.ON    = 1;          // Démarre Timer2
}

void init_adc() {
   /* Microphone initialization.
     * See Section 18.1 of the Basys MX3 datasheet. */
    TRISBbits.TRISB4 = 1; // RB4 (microphone) configured as input
    ANSELBbits.ANSB4 = 1; // Analog input enabled on RB4

    /* Step 0: Reset all ADC configuration registers to 0. */
    AD1CON1 = 0;
    AD1CON2 = 0;
    AD1CON3 = 0;

    /* Step 1: Microphone pin is configured as analog input
     * in the initialize_io*() function (see inputs_outputs.c). */

    /* Step 2: Select the analog input channel.
     * See p.241 of the PIC32MX datasheet. */
    AD1CHSbits.CH0SA = 4; // Select analog input 4 (positive input)
    AD1CHSbits.CH0NA = 0; // Select Vrefl as the negative input

    /* Step 3: Select result format.
     * See p.237 of the PIC32MX datasheet. */
    AD1CON1bits.FORM = 0; // 10-bit unsigned integer in 16-bit format

    /* Step 4: Select sampling clock source.
     * See p.237 of the PIC32MX datasheet. */
    AD1CON1bits.SSRC = 0b010; // Auto-convert triggered by Timer 3

    /* Step 5: Select voltage references.
     * See p.237 of the PIC32MX datasheet. */
    AD1CON2bits.VCFG = 0; // Vref+ = AVdd, Vref- = AVss

    /* Step 6: Disable input scan mode.
     * See p.239 of the PIC32MX datasheet. */
    AD1CON2bits.CSCNA = 0;

    /* Step 7: Set number of conversions per interrupt.
     * See p.239 of the PIC32MX datasheet. */
    AD1CON2bits.SMPI = 0; // One conversion per interrupt

    /* Step 8: Set buffer mode.
     * See p.239 of the PIC32MX datasheet. */
    AD1CON2bits.BUFM = 0; // Single 16-word buffer

    /* Step 9: Always use channel A for sampling.
     * See p.239 of the PIC32MX datasheet. */
    AD1CON2bits.ALTS = 0;

    /* Step 10: Select ADC clock source.
     * See p.240 of the PIC32MX datasheet. */
    AD1CON3bits.ADRC = 0; // Clock derived from PBCLK

    /* Step 11: Sample time setting is not required with selected SSRC.
     * See p.240 of the PIC32MX datasheet. */

    /* Step 12: ADC clock divider is not required with selected SSRC.
     * See p.240 of the PIC32MX datasheet. */

    /* Step 14: Configure ADC interrupts.
     * See p.64 of the PIC32MX datasheet. */
    IFS0bits.AD1IF = 0; // Clear ADC interrupt flag
    IEC0bits.AD1IE = 1; // Enable ADC interrupt
    IPC5bits.AD1IP = 4; // Set ADC interrupt priority to 6 (high)
    IPC5bits.AD1IS = 0; // Set subpriority to 0

    /* Step 15: Enable automatic sampling.
     * See p.238 of the PIC32MX datasheet. */
    AD1CON1bits.ASAM = 1;

    /* Step 13: Turn on the ADC module.
     * See p.237 of the PIC32MX datasheet. */
    AD1CON1bits.ON = 1;
}

void __ISR(_TIMER_3_VECTOR, IPL1AUTO) Timer3_ISR(void) { 
    
    IFS0bits.T3IF = 0;
};
