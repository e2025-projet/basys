/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Équipe 3 - Projet S4

  @File Name
    sensor.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#ifndef _SENSOR_H    /* Guard against multiple inclusion */
#define _SENSOR_H

#define CPU_FREQ 48000000
#define DEFAULT_SPEED_SOUND 343
#define DEFAULT_AMB_TEMP 20

#define DIST_100_GAIN 30
#define DIST_0_GAIN 5

#define GAIN_10_PERCENT 10
#define GAIN_0_PERCENT 0
#define GAIN_100_PERCENT 100

#define TRIG_PIN LATDbits.LATD11
#define ECHO_PIN PORTDbits.RD9


// Gain for noise cancellation output level
extern uint16_t gain_out;

/**
 * @brief Initializes the ultrasonic distance sensor system (HC-SR04).
 *
 * @param       en_temp_correction      If != 0, adjusts speed of sound based on temperature.
 * @param       temp                    Temperature in degrees Celsius, used if correction is enabled.
 *
 * Configures TRIG and ECHO pins, Timer2, and external interrupts INT2 and INT3.
 */
void initDistSensor(uint8_t en_temp_correction, uint8_t temp);


/**
 * @brief Calculates the speed of sound based on ambient temperature.
 *
 * @param       temp        Temperature in degrees Celsius.
 * @return                  Speed of sound in m/s.
 */
uint32_t calculateSpeedOfSound(uint8_t temp);


/**
 * @brief Enables the Timer2 interrupt used for generating the TRIG pulse.
 */
void enableDistISR();


/**
 * @brief Disables the Timer2 interrupt to stop triggering the TRIG pulse.
 */
void disableDistISR();


/**
 * @brief Calculates the distance in centimeters based on echo duration.
 * Note that the high level time can be calculated using the number of 
 * clock cycles / (CPU clock / 2). 
 *
 * Uses the formula from HC-SR04 datasheet:
 * Range = high level time * velocity / 2
 * 
 */
void calculateDistance();


/**
 * @brief Prints the measured gain on the LCD.
 *
 * Formats and displays the computed gain percentage based on distance.
 * The gain value is obtained from the getGain() function and displayed
 * on the LCD at line 1, position 0.
 */
void printGain();


void printDistance();


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
uint16_t getGain();


/**
 * @brief Sets the output gain value manually.
 *
 * @param       gain        Gain value to set (typically 0-100).
 */
void setGain(uint16_t gain);


/**
 * @brief Updates the gain value based on button inputs.
 *
 * Reads the current state of BTNU and BTND buttons and adjusts the gain
 * accordingly. BTNU increases gain by 10%, BTND decreases it by 10%.
 */
void updateGain();


/**
 * @brief Enables or disables the distance sensor functionality.
 *
 * @param       enable      If != 0, enables the distance sensor; otherwise disables it.
 */
void setDistSensor(uint8_t enable);


#endif

/* *****************************************************************************
 End of File
 */

