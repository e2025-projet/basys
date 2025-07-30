/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    fsm.c

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
#include "sys/attribs.h"
#include "config.h"
#include <stdbool.h>
#include "fsm.h"
#include "gain_out.h"
#include "lcd.h"
#include "ssd.h"
#include "app_commands.h"

char empty_string[16] = "               ";
anc_state_t current_state = STATE_OFF;
anc_state_t previous_state = STATE_OFF;
uint8_t prev_btnc = 0;
uint32_t counter_trig = 0;


/**
 * @brief Updates the ANC system state based on button input and handles state-specific logic.
 *
 * Manages state transitions via BTNC presses.
 * Handles distance sensor control and gain adjustment in ANC mode.
 * State transitions cycle through: OFF ? ANC ? HEAR_THROUGH.
 */
void updateState(void) {
    displayState();
    uint8_t curr_btnc = prt_BTN_BTNC;
    
    // Debounced button press: rising edge
    if (curr_btnc && !prev_btnc) {
        current_state = (current_state + 1) % NB_STATES;
    }
    
    if (previous_state != current_state) {
        switch (current_state) {
            case STATE_OFF:
                packetType = 1;
                UDP_Command_Buffer[SIGNATURE_LEN] = 'O';
                break;
            case STATE_ANC:
                packetType = 1;
                UDP_Command_Buffer[SIGNATURE_LEN] = 'N';
                break;
            case STATE_HEAR_THROUGH:
                packetType = 1;
                UDP_Command_Buffer[SIGNATURE_LEN] = 'H';
                break;
            default:
                break;
        }
    }
    
    if (current_state == STATE_ANC) {
        if (prt_SWT_SWT0) {
            setDistSensor(0); // Disable distance sensor
        } else if (counter_trig++ > 30) {
            setDistSensor(1); // Enable distance sensor
            enableDistISR();
            counter_trig = 0;
        }
        updateGain();
    }
    
    previous_state = current_state;
    
    prev_btnc = curr_btnc; // Save BTNC state for debouncing
}


/**
 * @brief Displays the current ANC state on the LCD.
 *
 * Shows the state name on line 0. In ANC mode, also displays the gain
 * percentage on line 1. For other states, clears line 1 with empty string.
 */
void displayState(void) {
    LCD_WriteStringAtPos(stateToString(current_state), 0, 0);
    if (current_state == STATE_ANC) {
        if (!prt_SWT_SWT7) printGain();
        else printDistance();
    } else {
        LCD_WriteStringAtPos(empty_string, 1, 0);
    }
}


/**
 * @brief Converts an ANC state enumeration to its string representation.
 *
 * @param       state       The ANC state to convert.
 * @return                  String representation of the state for LCD display.
 */
char* stateToString(anc_state_t state) {
    switch (state) {
        case STATE_OFF:
            return "----- Off ------";
        case STATE_ANC:
            return "----- ANC ------";
        case STATE_HEAR_THROUGH:
            return "- Hear-Through -";
        default:
            return empty_string;
    }
}

/* *****************************************************************************
 End of File
 */
