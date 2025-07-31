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

#ifndef _FSM_H    /* Guard against multiple inclusion */
#define _FSM_H

#define NB_STATES 3


// Enumeration for finite state machine
typedef enum {
    STATE_OFF = 0,
    STATE_ANC = 1,
    STATE_HEAR_THROUGH = 2
} anc_state_t;


/**
 * @brief Updates the ANC system state based on button input and handles state-specific logic.
 *
 * Manages state transitions via BTNC presses.
 * Handles distance sensor control and gain adjustment in ANC mode.
 * State transitions cycle through: OFF ? ANC ? HEAR_THROUGH.
 */
char* stateToString(anc_state_t state);


/**
 * @brief Displays the current ANC state on the LCD.
 *
 * Shows the state name on line 0. In ANC mode, also displays the gain
 * percentage on line 1. For other states, clears line 1 with empty string.
 */
void displayState();

void displayBlinkValue(uint16_t val);


/**
 * @brief Converts an ANC state enumeration to its string representation.
 *
 * @param       state       The ANC state to convert.
 * @return                  String representation of the state for LCD display.
 */
void updateState();

#endif

