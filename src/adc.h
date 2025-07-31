/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#ifndef _ADC_H    /* Guard against multiple inclusion */
#define _ADC_H
//
//// Threshold level for onboard microphone
//#define MIC_THRESHOLD 500

/* Initializes the ADC module to read analog input from the onboard microphone.
 * Configures ADC settings, input pin, trigger source, and interrupt priority.
 * This setup enables continuous sampling driven by Timer 3.
 */
void Initialize_ADC_Microphone();


#endif 

/* *****************************************************************************
 End of File
 */
