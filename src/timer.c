#include <xc.h>
#include <sys/attribs.h>
#include "config.h"
#include "timer.h"

void Timers_init() {
    _init_timer1();
    _init_timer2();
    _init_timer3();
    _init_timer4();
    _init_timer5();
}