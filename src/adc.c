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

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

#include "adc.h"
#include "led.h"

volatile uint16_t right_level = 0;
volatile uint16_t left_level  = 0;

/*
 * Lookup table for LD3 to LD0, where 0x0 and 0x0F correspond
 * respectively to levels 0 and 4.
*/
const uint16_t right_level_patterns[] = {
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
const uint16_t left_level_patterns[] = {
    0x0,  // 0 LED
    0x10, // 1 LED
    0x30, // 2 LED
    0x70, // 3 LED
    0xF0  // 4 LED
};


/* ISR for ADC3 : 
 * This routine reads the microphone input via ADC and calculates a volume level 
 * which is then visually represented on LEDs LD7 to LD0 as a mirrored bargraph.
 * Currently, the same signal is mirrored across both sides. 
 * In future updates, this will display independent volume levels for left and right 
 * MEMS microphones.
 */
void __ISR(_ADC_VECTOR, IPL6AUTO) ISR_ADC3_Microphone()
{
    uint16_t adc_value = ADC1BUF0;
    // Calculate the index level (1023 - 500) / (5 levels) = 105
    uint8_t index_level = (adc_value - MIC_THRESHOLD) / 105; 
    
    // Load the proper fields for LD7 to LD0 in their corresponding LUTs
    right_level = right_level_patterns[index_level] & 0x0F; 
    left_level  = left_level_patterns[index_level] & 0xF0; 
    
    // Reset all LEDs
    LATACLR = 0xFF; 
    // Turn on LEDs depending on the current volume level
    LATASET = left_level | right_level;
    // Reset interrupt flag
    IFS0bits.AD1IF = 0; 
}



/* Initializes the ADC module to read analog input from the onboard microphone.
 * Configures ADC settings, input pin, trigger source, and interrupt priority.
 * This setup enables continuous sampling driven by Timer 3.
 */
void Initialize_ADC_Microphone()
{
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
    IPC5bits.AD1IP = 6; // Set ADC interrupt priority to 6 (high)
    IPC5bits.AD1IS = 0; // Set subpriority to 0

    /* Step 15: Enable automatic sampling.
     * See p.238 of the PIC32MX datasheet. */
    AD1CON1bits.ASAM = 1;

    /* Step 13: Turn on the ADC module.
     * See p.237 of the PIC32MX datasheet. */
    AD1CON1bits.ON = 1;
}


