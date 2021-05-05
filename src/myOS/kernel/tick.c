#include "tick.h"
#include "wallClock.h"

unsigned long count = 99;

void initTick(void) {
    count = 99;
    setWallClockHook(showWallClock);
    setWallClock(23, 59, 59);
}

void tick(void) {
    count = (count + 1) % 100;
    
    if (count == 0) {
        updateWallClock();
    }
}