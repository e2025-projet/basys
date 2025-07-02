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
#define DIST_100_GAIN 30
#define DIST_0_GAIN 5

#define TRIG_PIN LATDbits.LATD11
#define ECHO_PIN PORTDbits.RD9

/**
 * @brief Initializes the ultrasonic distance sensor system (HC-SR04).
 *
 * @param       en_temp_correction      If != 0, adjusts speed of sound based on temperature.
 * @param       temp                    Temperature in degrees Celsius, used if correction is enabled.
 *
 * Configures TRIG and ECHO pins, Timer2, and external interrupts INT2 and INT3.
 */
void Init_Dist_Sensor(uint8_t en_temp_correction, uint8_t temp);


/**
 * @brief Calculates the speed of sound based on ambient temperature.
 *
 * @param       temp        Temperature in degrees Celsius.
 * @return                  Speed of sound in m/s.
 */
uint32_t Calculate_SpeedOfSound(uint8_t temp);


/**
 * @brief Enables the Timer2 interrupt used for generating the TRIG pulse.
 */
void Enable_DistISR();


/**
 * @brief Disables the Timer2 interrupt to stop triggering the TRIG pulse.
 */
void Disable_DistISR();


/**
 * @brief Calculates the distance in centimeters based on echo duration.
 * Note that the high level time can be calculated using the number of 
 * clock cycles / (CPU clock / 2). 
 *
 * Uses the formula from HC-SR04 datasheet:
 * Range = high level time * velocity / 2
 * 
 */
void Calculate_Distance();


/**
 * @brief Prints the measured clock cycles, distance, and gain on the LCD.
 *
 * Formats three debug strings:
 * - `clocks_nb`: raw timing in CPU clock cycles
 * - `distance` : measured distance in centimeters (commented out for now)
 * - `gain`     : computed gain percentage based on distance
 *
 * Only `clocks_str` and `gain_str` are currently displayed on the LCD.
 * The distance string (`dist_str`) can be enabled for additional debugging.
*/
void Print_Distance();


/**
 * @brief Computes a normalized gain value (0.0 to 1.0) based on measured distance.
 *
 * Gain is 0.0 if the distance is below `DIST_0_GAIN`,
 * 1.0 if the distance exceeds `DIST_100_GAIN`,
 * and linearly interpolated in between.
 *
 * @return Gain value between 0.0 (min) and 1.0 (max).
 */
float Get_Gain();

#endif

/* *****************************************************************************
 End of File
 */

