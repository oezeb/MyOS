#include "wallClock.h"
#include "vsprintf.h"
#include "vga.h"

int hh = 23;
int mm = 59;
int ss = 59;

typedef void (*hookfunc)(void);

hookfunc funcs[100] = {};

int func_count = 0;

void updateWallClock(void) {
        ss = (ss + 1) % 60;
        if (ss == 0) {
            mm = (mm + 1) % 60;
            if (mm == 0) {
                hh = (hh + 1) % 24;
            }
        }
        for (int i = 0; i < func_count; ++i) {
            funcs[i]();
        }
}

void setWallClock(int h, int m, int s) {
    hh = h;
    mm = m;
    ss = s;
}

void getWallClock(int*h, int*m, int*s) {
    *h = hh;
    *m = mm;
    *s = ss;
}

void setWallClockHook(void (*func)(void)) {
    funcs[func_count] = func;
    ++func_count;
}

char buf[10];
void showWallClock(void) {
    sprintf(buf, "%02d:%02d:%02d", hh, mm, ss);
    set_string_bottom(buf, VGA_COL - 9);
}
