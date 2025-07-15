/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.c

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#include <xc.h>
#include <sys/attribs.h>

#include <math.h>

#include "I2S.h"

volatile uint16_t pwm_val = 0;
volatile uint32_t raw_left  = 0;
volatile uint32_t raw_right  = 0;


void OC1_Init(void) {
    
    TRISBbits.TRISB14 = 0;   // Configure RB14 en sortie
    ANSELBbits.ANSB14 = 0;   // Désactive l'analogique sur RB14

    OC1CON  = 0;
    OC1R    = 0;
    OC1RS   = 0;
    
    RPB14R = 0x0C;            // RPB14R = 0x0C (assignation OC1 RB14)
    
    OC1CONbits.OCM    = 0b110; // Mode PWM sans fault pin
    OC1CONbits.OCTSEL = 1;     // Sélectionne Timer3 pour OC1
    
    OC1CONbits.ON     = 1;     // Active OC1
}

void Timer3_Init(void)
{
    T3CON = 0;
    T3CONbits.TCKPS = 0b000;      // Prédiviseur 1:1
    PR3             = 999;        // Valeur pour PR2 (767 - 62.5 kHz PWM base)
    TMR3            = 0;
    
    IPC3bits.T3IP   = 1;          // Priorité d'interruption
    IPC3bits.T3IS   = 0;
    IFS0bits.T3IF   = 0;          // Efface flag
    IEC0bits.T3IE   = 1;          // Active ISR Timer2
    
    T3CONbits.ON    = 1;          // Démarre Timer2
}


void SPI1_I2S_Config(void)
{
    TRISFbits.TRISF5 = 1;
    TRISFbits.TRISF4 = 1;
    
    // --- Set SPI pins ---
    TRISFbits.TRISF8 = 0;         // SS2 output
    TRISFbits.TRISF6 = 1;         // SDI input ()
    TRISFbits.TRISF6 = 0;         // SCK2 output ()

    RPF8R  = 0b0111;              // SS1 = RF8 ()
    SDI1R  = 0x0F;                 // SDI1 = RPF6

    // --- Disable SPI before config ---
    SPI1CONbits.ON = 0;           // Ensure OFF before config
    
    SPI1CON = 0;
    SPI1CON2 = 0;
    SPI1STAT = 0;
   
    // --- SPI2 I²S configuration ---
    SPI1CONbits.MSTEN   = 1;      // Master mode
    SPI1CONbits.MODE32  = 1;      // 32-bit mode
    SPI1CONbits.MODE16  = 0;
    SPI1CONbits.ENHBUF  = 1;      // Enhanced Buffer mode
    
    SPI1CONbits.SRXISEL = 0b11;

    SPI1CON2bits.AUDEN  = 1;      // I²S mode
    SPI1CON2bits.AUDMOD = 0;      // Standard I²S

    SPI1BRG = 5;                  // ~4 MHz BCLK (Pclk = 48 MHz)

    // --- Interrupt setup ---
    IFS1bits.SPI1RXIF = 0;        // Clear interrupt flag
    IEC1bits.SPI1RXIE = 1;        // Enable SPI2 RX interrupt
    IPC7bits.SPI1IP = 2;          // Priority level
    IPC7bits.SPI1IS = 0;

    // --- Turn SPI2 ON *after* full config ---
    SPI1CONbits.ON = 1;
}

void __ISR(_SPI_1_VECTOR, IPL2AUTO) SPI1_ISR(void)
{
    // Clear overflow if it happened
    if (SPI1STATbits.SPIROV) {
        SPI1STATCLR = 1 << 6;
    }

    // Read all samples in FIFO
    while (SPI1STATbits.RXBUFELM > 1) {
        uint32_t left_raw  = SPI1BUF;
        uint32_t right_raw = SPI1BUF;

        // Convert to mono
        int32_t left  = ((int32_t)left_raw) >> 8; // 32 bits to 24 bits
        int32_t right = ((int32_t)right_raw) >> 8;
        
        int32_t mono = (PORTFbits.RF5) ? left : right;
        if (PORTFbits.RF4) mono = (left + right) >> 1;
     
        mono = mono >> 14;
        
        mono = mono * 2;
        
        
        if (mono < -512) mono = -512;
        if (mono > 511) mono = 511;
        mono += 512;

        pwm_val = (uint16_t)mono;
    }

    IFS1bits.SPI1RXIF = 0; // Clear interrupt flag
}

/* ISR de Timer2 : gère sortie audio PWM */
void __ISR(_TIMER_3_VECTOR, IPL1AUTO) Timer3_ISR(void) { 
    
    OC1RS = pwm_val;   
    IFS0bits.T3IF = 0;
};

/* ************************** ***************************************************
 End of File
 */
