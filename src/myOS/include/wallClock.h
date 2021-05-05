#ifndef __KERNEL_WALLCLOCK_H__
#define __KERNEL_WALLCLOCK_H__

void updateWallClock(void);

void setWallClock(int h, int m, int s);  //设置墙钟的开始时间
void getWallClock(int*h, int*m, int*s);  //读取墙钟

void setWallClockHook(void (*func)(void));
void showWallClock(void);

#endif