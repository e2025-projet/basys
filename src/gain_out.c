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
#include <stdio.h>
#include "sys/attribs.h"

#include "gain_out.h"
#include "lcd.h"
#include "config.h"

// Strings for debug purposes (used for printing clock cycles/distance/gain)
char clocks_str[16];
char dist_str[16];
char gain_str[16];

// Current and previous button states
uint8_t curr_btnu, prev_btnu = 0;
uint8_t curr_btnd, prev_btnd = 0;

// Flag for enabling/disabling the distance sensor
uint8_t dist_sensor_en = 1;

// Speed of sound depending on ambient temperature
float speed_sound = 0;
// Distance calculated from HC-SR04 distance sensor
volatile uint32_t distance = 0;

// Gain for noise cancellation output level
uint16_t gain_out = GAIN_100_PERCENT; 

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
void __ISR(_TIMER_2_VECTOR, IPL7AUTO) isrTimer2Sensor() {
    if (!trig_done) {
        // Start TRIG pulse
        TRIG_PIN = 1;
        trig_done = 1;
    }
    else { // In normal conditions, counter condition is unnecessary
        // Drop TRIG pulse
        TRIG_PIN = 0;
        // Reset flag and counter
        trig_done = 0;
        counter = 0;
        // Disable Timer2 interrupt after pulse
        disableDistISR();
    }
//    counter++;
    IFS0bits.T2IF = 0; // Reset interrupt flag
}


/**
 * @brief Interrupt handler for INT2 (ECHO rising edge).
 *
 * This ISR stores the core timer value when the ECHO signal starts (rising edge).
 * Used to timestamp the beginning of the ultrasonic echo pulse.
 */
void __ISR(_EXTERNAL_2_VECTOR, IPL1AUTO) int2Handler(void) {
    // Capture start time
    echo_start = _CP0_GET_COUNT();
    // Clear interrupt flag
    IFS0bits.INT2IF = 0;
}


/**
 * @brief Interrupt handler for INT3 (ECHO falling edge).
 *
 * This ISR calculates the number of core clock cycles between the start and end
 * of the echo pulse and calculates the corresponding distance.
 */
void __ISR(_EXTERNAL_3_VECTOR, IPL1AUTO) int3Handler(void) {
    // Calculate duration in clock cycles
    clocks_nb = (int32_t)((_CP0_GET_COUNT() - echo_start));
    // Calculate distance based on timing
    calculateDistance();
    // Disable TRIG to prevent multiple triggers
    disableDistISR();
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
void initDistSensor(uint8_t en_temp_correction, uint8_t temp) {
    // Calculate speed of sound depending (or not) on the ambient temperature
    speed_sound = (!en_temp_correction) ? DEFAULT_SPEED_SOUND : calculateSpeedOfSound(temp);
    
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
    INTCONbits.INT3EP = 0;  // Falling edge
    INT3R = 3;              // Map INT3 to RPD10
 }


/**
 * @brief Enables the Timer2 interrupt used for generating the TRIG pulse.
 */
void enableDistISR() {
    IEC0bits.T2IE = 1;
}


/**
 * @brief Disables the Timer2 interrupt to stop triggering the TRIG pulse.
 */
void disableDistISR() {
    IEC0bits.T2IE = 0;
}


/**
 * @brief Enables or disables the distance sensor functionality.
 *
 * @param       enable      If = 1, enables the distance sensor; otherwise disables it.
 */
void setDistSensor(uint8_t enable) {
    dist_sensor_en = enable;
}


/**
 * @brief Calculates the speed of sound based on ambient temperature.
 *
 * @param       temp        Temperature in degrees Celsius.
 * @return                  Speed of sound in m/s.
 */
uint32_t calculateSpeedOfSound(uint8_t temp) {
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
void calculateDistance() {
    // Calculate the current distance in centimeters
    distance = (uint32_t)(clocks_nb*100*speed_sound / (CPU_FREQ*2));
}


/**
 * @brief Prints the measured gain on the LCD.
 *
 * Formats and displays the computed gain percentage based on distance.
 * The gain value is obtained from the getGain() function and displayed
 * on the LCD at line 1, position 0.
 */
void printGain() {
    // Generate string for gain percentage
    sprintf(gain_str, "  Gain: %3d %%   ", getGain());

    // Show gain string on LCD
    LCD_WriteStringAtPos(gain_str, 1, 0);
}


/**
 * @brief Computes a normalized gain value (0 to 100) based on measured distance.
 *
 * Gain is 0 if the distance is below DIST_0_GAIN,
 * 100 if the distance exceeds DIST_100_GAIN,
 * and linearly interpolated in between.
 * If the distance sensor is disabled, returns the manually set gain value.
 *
 * @return Gain value between 0 (min) and 100 (max).
 */
uint16_t getGain() {
    if (!dist_sensor_en) return gain_out;
    else if (distance >= DIST_100_GAIN) return GAIN_100_PERCENT;
    else if (distance <= DIST_0_GAIN) return GAIN_0_PERCENT; 
    else return (uint16_t)((distance - DIST_0_GAIN) * 100) / (DIST_100_GAIN - DIST_0_GAIN);
}


/**
 * @brief Sets the output gain value manually.
 *
 * @param       gain        Gain value to set (typically 0-100).
 */
void setGain(uint16_t gain) {
    gain_out = gain;
}


/**
 * @brief Updates the gain value based on button inputs.
 *
 * Reads the current state of BTNU and BTND buttons and adjusts the gain
 * accordingly. BTNU increases gain by 10%, BTND decreases it by 10%.
 */
void updateGain() {
    // Capture the buttons state for the output gain
    curr_btnu = prt_BTN_BTNU;
    curr_btnd = prt_BTN_BTND;
    
    if (curr_btnu && !prev_btnu && gain_out != GAIN_100_PERCENT) {
        gain_out += GAIN_10_PERCENT;
    }
    else if (curr_btnd && !prev_btnd && gain_out != GAIN_0_PERCENT) {
        gain_out -= GAIN_10_PERCENT;
    }
    
    // Update the previous BTNU and BTND for debouncing
    prev_btnu = curr_btnu;
    prev_btnd = curr_btnd;
}