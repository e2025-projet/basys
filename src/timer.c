#include <xc.h>
#include <sys/attribs.h>
#include "config.h"
#include "timer.h"
#include <stdbool.h>
#include "app_commands.h"
#include "I2S.h"

void Timers_init() {
    _init_timer3();
    _init_timer4();
}

void Timers_actions() {
    //_init_timer2();
    //_init_timer3();
    //_init_timer4();
    //_action_timer4();
}

// Timer3 Initialization with Interrupt
void _init_timer3() {
    T3CON = 0;
    TMR3 = 0;
    PR3 = 52082;

    T3CONbits.TCKPS = 0b111;
    T3CONbits.TCS = 0;

    IFS0bits.T3IF = 0;
    IEC0bits.T3IE = 1;
    IPC3bits.T3IP = 3;
    IPC3bits.T3IS = 0;

    T3CONbits.ON = 1;
}

// Timer4 Initialization with Interrupt

// TIMER 4 HANDLES RECEPTION
void _init_timer4() {
    T4CON = 0;
    TMR4 = 0;
    PR4 = 3016; 

    T4CONbits.TCKPS = 0b111;
    T4CONbits.TCS = 0;
    T4CONbits.T32 = 0;

    IFS0bits.T4IF = 0;
    IEC0bits.T4IE = 1;
    IPC4bits.T4IP = 3;
    IPC4bits.T4IS = 0;

    T4CONbits.ON = 1;
}

void __ISR(_TIMER_3_VECTOR, IPL3AUTO) Timer3Handler(void) {
    IFS0bits.T3IF = 0;
}

void __ISR(_TIMER_4_VECTOR, IPL3AUTO) Timer4Handler(void) {
    UDP_Check_Reception = 1;
    IFS0bits.T4IF = 0;
}

