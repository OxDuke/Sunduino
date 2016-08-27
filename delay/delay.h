#ifndef DELAY_H
#define DELAY_H

#include "sys.h"

void sysTickInit(uint8_t sysClkFreq);

void delayUs(uint32_t nus);
void delayMs(uint16_t nms);

uint64_t getTimeMicros(void);
uint64_t getTimeMillis(void);

#endif /* DELAY_H */
