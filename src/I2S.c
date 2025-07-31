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
#include "config.h"

#include "lcd.h"

#include <stdio.h>
#include <stdbool.h>
#include "I2S.h"
#include "gain_out.h"
#include "app_commands.h"

#include "filterIIRCoeffs.h"

/*
 * Lookup table for LD3 to LD0, where 0x0 and 0x0F correspond
 * respectively to levels 0 and 4.
*/
const uint8_t right_level_patterns[] = {
    0x0,  // 0 LED
    0x08, // 1 LED
    0x0C, // 2 LED
    0x0E, // 3 LED
    0x0F  // 4 LED
};

/*
 * Lookup table for LD4 to LD7, where 0x0 and 0xF0 correspond
 * respectively to levels 0 and 4.
*/
const uint8_t left_level_patterns[] = {
    0x0,  // 0 LED
    0x10, // 1 LED
    0x30, // 2 LED
    0x70, // 3 LED
    0xF0  // 4 LED
};

// Left and right levels for bargraph volume (LD4 - LD7 and LD3 - LD0)
volatile uint8_t right_level = 0;
volatile uint8_t left_level  = 0;

volatile uint16_t pwm_val = 0;
volatile uint32_t raw_left  = 0;
volatile uint32_t raw_right  = 0;

volatile uint32_t left_unsigned = 0;
volatile uint32_t right_unsigned = 0;

// Your I2S samples are 18-bit signed (range ? -131072 to +131071)
const int32_t FULL_SCALE = 131072;  // 2^17
const int32_t PWM_MAX = 1023;
int32_t mono;

char string_spi[16];

void OC1_Init(void) {
    // Setup Timer 2
    // Config @ 48 kHz
    IFS0bits.T2IF = 0;       // Clear interrupt flag
    IEC0bits.T2IE = 1;       // Enable interrupt
    IPC2bits.T2IP = 1;       // Priority
    IPC2bits.T2IS = 0;       // Subpriority
    
    // Setup speaker
    RPB14R = 0b1100 ; // RD3 mapped to OC1
    TRISBbits.TRISB14 = 0;
    ANSELBbits.ANSB14 = 0;
    
    T2CONbits.TCKPS = 0b00 ;
    TMR2 = 0x0;
    
    PR2 = 1023 ; // P�riode du PWM = 1023 = PR2 + 1
    
    // Setup OC1
    OC1CON = 0x0;
   
    OC1CONbits.OC32 = 0; // 16 bit compare timer source
    OC1CONbits.OCTSEL = 0; // Timer 2 is used
    OC1CONbits.OCM = 0b110; // PWM Mode w/o fault pin
    OC1CONbits.ON = 0;
    
    OC1R  = 0; 
    OC1RS = 0;
    
    // Start timer then OC1
    T2CONbits.ON = 1;
    OC1CONbits.ON = 1;
}

  
void SPI1_I2S_Config(void)
{

    // --- Set SPI pins ---
    TRISFbits.TRISF8 = 0;         // SS2 output
    TRISFbits.TRISF6 = 1;         // SDI input ()

    RPF8R  = 0b0111;              // SS1 = RF8 ()
    SDI1R  = 0x0F;                 // SDI1 = RPF6

    // --- Disable SPI before config ---
    SPI1CONbits.ON = 0;           // Ensure OFF before config
    
    SPI1CON = 0;
    SPI1CON2 = 0;
    SPI1STAT = 0;
   
    // --- SPI2 I�S configuration ---
    SPI1CONbits.MSTEN   = 1;      // Master mode
    SPI1CONbits.MODE32  = 1;      // 32-bit mode
    SPI1CONbits.MODE16  = 0;
    SPI1CONbits.ENHBUF  = 1;      // Enhanced Buffer mode
    
    SPI1CONbits.SRXISEL = 0b11;

    SPI1CON2bits.AUDEN  = 1;      // I�S mode
    SPI1CON2bits.AUDMOD = 0;      // Standard I�S

    SPI1BRG = 11;                  // ~3 MHz BCLK (Pclk = 48 MHz)

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
    uint32_t left_raw, right_raw;
    
    // Clear overflow if it happened
    if (SPI1STATbits.SPIROV) {
        SPI1STATCLR = 1 << 6;
    }

    // Read all samples in FIFO
    while (SPI1STATbits.RXBUFELM > 1) {
        // If SW3 is on, invert the left/right microphones inputs so it matches with the LEDs
        if (prt_SWT_SWT3) {
            left_raw  = SPI1BUF;
            right_raw = SPI1BUF;
        } else {
            right_raw  = SPI1BUF;
            left_raw = SPI1BUF;
        }
        
        // Convert each channel to 18 bits
        int32_t left  = ((int32_t)left_raw) >> 14; 
        int32_t right = ((int32_t)right_raw) >> 14; 
        
        // Enable/disable the IIR lowpass filter based on SW2
        uint8_t IIREnabled = !prt_SWT_SWT2;
        // Inputs/outputs for the IIR 4th order lowpass filter 
        int32_t in_left, out_left, in_right, out_right, nSOS = 0;
        
        // Intialize inputs for the IIR filter
        in_left = left;
        in_right = right;
        
        // If IIR filtering is enabled, real-time calculation of the next output sample
        if (IIREnabled) {
            out_right = in_right;
            out_left = in_left;
            
            for (nSOS = 0; nSOS < N_SOS_SECTIONS; nSOS++) {

                // 1) y[n] = b0�x[n] + v[n1]
                out_left = IIRCoeffs[nSOS][0] * in_left + IIRv_left[nSOS];
                out_right = IIRCoeffs[nSOS][0] * in_right + IIRv_right[nSOS];
                
                // Convert back to 16 bits
                out_left = (int16_t)(out_left >> 13);
                out_right = (int16_t)(out_right >> 13);

                // 2) compute new v[n] = b1�x[n] ? a1�y[n] + u[n?1]
                IIRv_left[nSOS] = IIRCoeffs[nSOS][1] * in_left - IIRCoeffs[nSOS][4] * out_left + IIRu_left[nSOS];
                IIRv_right[nSOS] = IIRCoeffs[nSOS][1] * in_right - IIRCoeffs[nSOS][4] * out_right + IIRu_right[nSOS];   
                
                // 3) compute new u[n] = b2�x[n] ? a2�y[n]
                IIRu_left[nSOS] = IIRCoeffs[nSOS][2] * in_left - IIRCoeffs[nSOS][5] * out_left;
                IIRu_right[nSOS] = IIRCoeffs[nSOS][2] * in_right - IIRCoeffs[nSOS][5] * out_right;

                in_left = out_left;
                in_right = out_right;
            }
            
            // Copy the resulting filtered sample to the current output buffer
            left = out_left;
            right = out_right;
            
        }
        
        if (!prt_SWT_SWT3) {
            // choose whichever channel has larger magnitude
            if (abs(left) > abs(right))
                mono = left;
            else
                mono = right;
            }
        else {
            mono = prt_SWT_SWT1 ? left : right;
        }
        
        // Apply dynamic range compression instead of simple bit shifting
        uint16_t audio_value = compress_audio_linear(mono);
        
        // Apply dynamic range compression instead of simple bit shifting
        pwm_val = audio_value; 
        
        // Calculate the index level
        uint8_t index_level_left = (compress_audio_linear(left) - 700) / 105; 
        uint8_t index_level_right = (compress_audio_linear(right) - 640) / 105; 

        // Load the proper fields for LD7 to LD0 in their corresponding LUTs
        right_level = right_level_patterns[index_level_right] & 0x0F; 
        left_level  = left_level_patterns[index_level_left] & 0xF0; 

        // Reset all LEDs
        LATACLR = 0xFF; 
        // Turn on LEDs depending on the current volume level
        LATASET = left_level | right_level;
        
        if (dataReady == 0) {
            uint8_t MSB_send = mono >> 10 & 0xFF;
            uint8_t LSB_send = mono >> 2 & 0xFF;
            // 18 bits -> 2x 8 bits
            UDP_Send_Buffer[SIGNATURE_LEN + dataPtr++] = MSB_send;
            UDP_Send_Buffer[SIGNATURE_LEN + dataPtr++] = LSB_send;
            
            if (dataPtr >= DATA_LEN) {
                dataPtr = 0;
                dataReady = 1;
            }
        }
    }

    IFS1bits.SPI1RXIF = 0; // Clear interrupt flag
}

uint16_t compress_audio_linear(int32_t input_18bit) {
    // 1) magnitude
    uint32_t abs_value = (input_18bit < 0)
                        ? (uint32_t)(-input_18bit)
                        : (uint32_t) input_18bit;

    // 2) soft-knee at 25% of max (32768)
    const uint32_t KNEE_POINT = (1 << 17) / 4;  // 32768
    const uint32_t COMP_RATIO = 4;             // 4:1 post-knee

    if (abs_value > KNEE_POINT) {
        uint32_t over = abs_value - KNEE_POINT;
        abs_value = KNEE_POINT + (over / COMP_RATIO);
    }

    // 3) down-shift to 10 bits
    uint16_t result = (uint16_t)(abs_value >> 4);

    // 4) clamp to [1?1023]
    if (result > 1023) result = 1023;
    if (result <    1) result =    1;
    return result;
}

// Output timer please fchiing work man i swear
void __ISR(_TIMER_2_VECTOR, IPL1AUTO) Timer2_ISR(void) { 
    
    OC1RS = pwm_val; 
    
    IFS0bits.T2IF = 0;
};


/* ISR de Timer2 : g�re sortie audio PWM */
/*
void __ISR(_TIMER_3_VECTOR, IPL1AUTO) Timer3_ISR(void) { 
    
    OC1RS = (uint16_t) pwm_val * gain_out / 100;   
    IFS0bits.T3IF = 0;
};*/

/* ************************** ***************************************************
 End of File
 */
