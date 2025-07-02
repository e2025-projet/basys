/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    I2S.c

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#include <xc.h>
#include <sys/attribs.h>

#include "I2S.h"


//#define BAUDRATE 115200
//#define SAMPLE_RATE 8000
//
//volatile int downsample_counter = 0;
//
//void UART_Init(void) {
//    
//    // UART4 to RPF12 for USB-UART
//    TRISFbits.TRISF12 = 0;  // RF12 as output
//    RPF12R = 0x02; // RF12 ? U4TX
//    
//    U4MODE = 0;
//    U4BRG = 25;
//    U4STA = 0;
//    U4MODEbits.ON = 1;
//    U4STAbits.UTXEN = 1;
//}
//
//void UART_WriteByte(uint8_t b) {
//    while (U4STAbits.UTXBF);
//    U4TXREG = b;
//}
//
//void Send_Audio_Sample(int32_t sample) {
//    uint16_t val = (sample >> 8) + 32768;  // Convert to unsigned
//    UART_WriteByte(val & 0xFF);           // LSB
//    UART_WriteByte((val >> 8) & 0xFF);    // MSB
//}


void SPI2_I2S_Config(void)
{
    TRISAbits.TRISA3 = 0;
    
    // Set SPI pins
    TRISCbits.TRISC2 = 0;         // SS2 output
    TRISCbits.TRISC1 = 1;         // SDI input (JA2)
    
    TRISGbits.TRISG6 = 0;         // SCK2 output (JA4)
    RPC2R = 0b0110;               // SS2 = RC2 (JA1)
    SDI2R  = 0x0A; 
    
    // --- SPI2 in I²S mode (master) ---
    
    SPI2CON2 = 0;

    SPI2CON2bits.AUDEN  = 1;    // I²S mode
    SPI2CON2bits.AUDMOD = 0;    // Standard I²S
    SPI2CONbits.MSTEN   = 1;    // Master mode
    SPI2CONbits.MODE32  = 1;
    SPI2CONbits.MODE16  = 0;
    SPI2CONbits.ENHBUF  = 1;

    SPI2BRG = 7; // ~3.0 MHz BCLK = 6
    
    IEC1bits.SPI2RXIE   = 1;    // Enable SPI2 RX interrupt
    IPC8bits.SPI2IP     = 5;    // Priority (1?7)
    IPC8bits.SPI2IS     = 0;
    IFS1bits.SPI2RXIF   = 0;    // Clear flag before enabling

    SPI2CONbits.ON = 1;
}

void __ISR(_SPI_2_VECTOR, IPL5SOFT) SPI2_ISR(void)
{
//    uint32_t raw = SPI2BUF;
//    int32_t sample = (int32_t)(raw >> 8);  // 24-bit audio
//
//    if (++downsample_counter >= 6) {  // Downsample from 48k to ~8k
//        downsample_counter = 0;
//        Send_Audio_Sample(sample);
//    }
//    static int counter = 0;
//    if (++counter >= 1000) {
//        LATAINV = (1 << 3);  // Toggle LED A3 every 1000 samples
//        counter = 0;
//    }
    
    IFS1bits.SPI2RXIF = 0;
    SPI2BUF = 0;
}

/* ************************** ***************************************************
 End of File
 */
