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

#ifndef _UART_YBL_H    /* Guard against multiple inclusion */
#define _UART_YBL_H

/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif   
    
    
// Threshold level for onboard microphone
#define MIC_THRESHOLD 512
#define DATA_LEN 1024
   
volatile uint8_t dataReady;
volatile char dataChar[DATA_LEN];
volatile uint16_t dataPtr;
    
void OC1_Init(void);

void Timer3_Init(void);

void SPI1_I2S_Config(void);

uint16_t compress_audio_linear(int32_t input_24bit);

#ifdef __cplusplus
}
#endif

#endif /* _UART_YBL_H */

/* *****************************************************************************
 End of File
 */
