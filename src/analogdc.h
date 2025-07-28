/* ************************************************************************** */
/** 
 * Auteur : JG et OP
 * Fichier : analogdc.h
************************************************************************** */

#ifndef _ANALOGDC_H    /* Guard against multiple inclusion */
#define _ANALOGDC_H

/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif
#define ADC_LEN 128
    
extern unsigned char ADC_Send[ADC_LEN];
extern volatile int adc_ptr;
extern volatile uint8_t adc_ready;
extern uint32_t sum;
extern char charSum[12];

void init_adc();

void start_adc();

void stop_adc();

void send_adc_val();

void init_timer3();

    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _SETUP_H */

/* *****************************************************************************
 End of File
 */
