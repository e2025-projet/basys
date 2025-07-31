// S4 Timers

#ifndef _TIMERS_H    /* Guard against multiple inclusion */
#define _TIMERS_H

#ifdef __cplusplus
extern "C" {
#endif
uint8_t timer4_pop;
    
void Timers_init();
void Timers_actions();
void _init_timer2();
void _init_timer3();
void _init_timer4();

void _action_timer4();

#ifdef __cplusplus
}
#endif

#endif 
