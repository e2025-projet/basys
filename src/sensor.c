/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Équipe 3 - Projet S4

  @File Name
    sensor.c

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
#include <xc.h>

#include "sensor.h"
#include "sys/attribs.h"
#include "lcd.h"
#include <stdio.h>

// Strings for debug purposes (used for printing clock cycles/distance)
char clocks_str[16];
char dist_str[16];

// Speed of sound depending on ambient temperature
float speed_sound = 0;
// Distance calculated from HC-SR04 distance sensor
volatile float distance = 0;
// Duration of ECHO signal in CPU clock cycles 
volatile int32_t clocks_nb = 0;
// Saved value from ECHO signal rising edge 
volatile uint64_t echo_start = 0;
// Flag for TRIG signal
volatile uint8_t trig_done = 0;
// Counter used to generate TRIG signals with a frequency < than 100 kHz
volatile uint32_t counter = 0;


/**
 * @brief Timer2 interrupt service routine (ISR) used to generate a 10 µs pulse on TRIG_PIN.
 *
 * This ISR is triggered by Timer2 at a configured frequency. The pulse is used to trigger
 * an ultrasonic sensor. After sending the pulse, the ISR disables itself.
 */
void __ISR(_TIMER_2_VECTOR, IPL7AUTO) ISR_Timer2_Sensor() {
    if (!trig_done) {
        // Start TRIG pulse
        TRIG_PIN = 1;
        trig_done = 1;
    }
    else if (counter == 10) { // In normal conditions, counter condition is unnecessary
        // Drop TRIG pulse
        TRIG_PIN = 0;
        // Reset flag and counter
        trig_done = 0;
        counter = 0;
        // Disable Timer2 interrupt after pulse
        Disable_DistISR();
    }
    counter++;
    IFS0bits.T2IF = 0; // Reset interrupt flag
}


/**
 * @brief Interrupt handler for INT2 (ECHO rising edge).
 *
 * This ISR stores the core timer value when the ECHO signal starts (rising edge).
 * Used to timestamp the beginning of the ultrasonic echo pulse.
 */
void __ISR(_EXTERNAL_2_VECTOR, IPL1AUTO) INT2_Handler(void) {
    // Capture start time
    echo_start = _CP0_GET_COUNT();
    // Clear interrupt flag
    IFS0bits.INT2IF = 0;
}


/**
 * @brief Interrupt handler for INT3 (ECHO falling edge).
 *
 * This ISR calculates the number of core clock cycles between the start and end
 * of the echo pulse and prints the corresponding distance.
 */
void __ISR(_EXTERNAL_3_VECTOR, IPL1AUTO) INT3_Handler(void) {
    // Calculate duration in clock cycles
    clocks_nb = (int32_t)((_CP0_GET_COUNT() - echo_start));
    // Debug print on LCD (will be disabled in future)
    Calculate_Distance();
    Print_Distance();
    // Disable TRIG to prevent multiple triggers
    Disable_DistISR();
    // Clear interrupt flag
    IFS0bits.INT3IF = 0;
}


/**
 * @brief Initializes the ultrasonic distance sensor system (HC-SR04).
 *
 * @param       en_temp_correction      If != 0, adjusts speed of sound based on temperature.
 * @param       temp                    Temperature in degrees Celsius, used if correction is enabled.
 *
 * Configures TRIG and ECHO pins, Timer2, and external interrupts INT2 and INT3.
 */
void Init_Dist_Sensor(uint8_t en_temp_correction, uint8_t temp) {
    // Calculate speed of sound depending (or not) on the ambient temperature
    speed_sound = (!en_temp_correction) ? DEFAULT_SPEED_SOUND : Calculate_SpeedOfSound(temp);
    
    // Initialize TRIG and ECHO pins
    TRISDbits.TRISD11 = 0;  // RD11 as output (TRIG)
    TRISDbits.TRISD9 = 1;   // RD9 as input (ECHO rising edge)
    TRISDbits.TRISD10 = 1;  // RD10 as input (ECHO falling edge)
    
    // Configure Timer2 for sensor timing 
    T2CON = 0;              // Reset Timer2 control register
    T2CONbits.TCKPS = 4;    // 1:16 prescale value
    T2CONbits.TCS = 0;      // PCBLK input (the default)
    T2CONbits.ON = 1;       // Turn on Timer2
    PR2 = 29;               // f = 100 kHz (for 10us TRIG)
    IEC0bits.T2IE = 1;      // Enable interrupts for Timer2
    IFS0bits.T2IF = 0;      // Reset interrupt flag
    IPC2bits.T2IP = 7;      // Set interrupt priority
    IPC2bits.T2IS = 0;      // Set interrupt subpriority
    
    // INT1 config
    IFS0bits.INT2IF = 0;    // Reset interrupt flag
    IEC0bits.INT2IE = 1;    // Enable interrupts for INT2
    IPC2bits.INT2IP = 1;    // Set interrupt priority
    IPC2bits.INT2IS = 0;    // Set interrupt subpriority
    INTCONbits.INT2EP = 1;  // Rising edge
    INT2R = 0;              // Map INT2 to RPD9
    
    // INT3 config
    IFS0bits.INT3IF = 0;    // Reset interrupt flag
    IEC0bits.INT3IE = 1;    // Enable interrupts for INT3
    IPC3bits.INT3IP = 1;    // Set interrupt priority
    IPC3bits.INT3IS = 0;    // Set interrupt subpriority
    INTCONbits.INT3EP = 0;  // Rising edge
    INT3R = 3;              // Map INT3 to RPD10
 }


/**
 * @brief Enables the Timer2 interrupt used for generating the TRIG pulse.
 */
void Enable_DistISR() {
    IEC0bits.T2IE = 1;
}


/**
 * @brief Disables the Timer2 interrupt to stop triggering the TRIG pulse.
 */
void Disable_DistISR() {
    IEC0bits.T2IE = 0;
}


/**
 * @brief Calculates the speed of sound based on ambient temperature.
 *
 * @param       temp        Temperature in degrees Celsius.
 * @return                  Speed of sound in m/s.
 */
uint32_t Calculate_SpeedOfSound(uint8_t temp) {
    // Speed of sound is impacted by ambient temperature
    return (uint32_t)(331.35 + 0.606*temp);
}


/**
 * @brief Calculates the distance in centimeters based on echo duration.
 * Note that the high level time can be calculated using the number of 
 * clock cycles / (CPU clock / 2). 
 *
 * Uses the formula from HC-SR04 datasheet:
 * Range = high level time * velocity / 2
 * 
 */
void Calculate_Distance() {
    // Calculate the current distance in centimeters
    distance = (float)(clocks_nb*100*speed_sound / (CPU_FREQ*2));
}


/**
 * @brief Prints the measured clock cycles and distance on the LCD.
 *
 * Formats two strings showing:
 * - `clocks_nb` (raw timing in CPU clock cycles)
 * - `distance` (in centimeters)
 */
void Print_Distance() {
    // Generate both strings for clock cycles and distance in centimeters
    sprintf(clocks_str, "Clocks: %d", clocks_nb);
    sprintf(dist_str, "Dist: %.2f cm", distance);
    // Show on display (used for debug purposes)
    LCD_DisplayClear();
    LCD_WriteStringAtPos(clocks_str, 0, 0);
    LCD_WriteStringAtPos(dist_str, 1, 0);
}
