#include "sys.h"
#include "delay.h"

//#include "Sunduino.h"

static uint8_t  facUs = 0;	//the number of systicks during 1 microsecond
//static uint16_t facMs = 0;	//the number of systicks during 1 milisecond

//static uint32_t microseconds = 0;
static uint32_t milliseconds = 0; //overflow in about 49 days

#define ENABLE_SYSTICK_INTERRUPT()   SysTick->CTRL |= (1 << 1)
#define DISABLE_SYSTICK_INTERRUPT()  SysTick->CTRL &= ~(1 << 1)

#define CLOCK_FREQUENCY 168  //in MHz

/**
 * SysTick initilization
 * @param sysClkFreq system clock frequency, usually 168Mhz
 */
void sysTickInit(uint8_t sysClkFreq)
{
	uint32_t reloadValue;

	SysTick->CTRL &= ~(1 << 2);	//SysTick clocksource = HCLK/8

	//calculate reloadValue, here set it to generate a 1ms interrupt
	//on a sysClkFreq=168MHz chip
	reloadValue = sysClkFreq / 8 * 1000;

	facUs = sysClkFreq / 8; //calculate facUs

	ENABLE_SYSTICK_INTERRUPT();  //enable SysTick interrupt
	SysTick->LOAD = reloadValue;   //interrupt comes every 1/delay_ostickspersec
	SysTick->CTRL |= 1 << 0;  //enable SysTick
}

/**
 * [delayUs description]
 * @param nus number of microseconds, range:[0,204522252]
 *        (204522252 = 2^32/facUs@facUs=21)
 */
void delayUs(uint32_t nus)
{
	uint32_t ticks;
	uint32_t told, tnow, tcnt = 0;
	uint32_t reload = SysTick->LOAD;	

	ticks = nus * facUs; 				//calculate number of ticks
	told = SysTick->VAL;        		//get told
	while (1)
	{
		tnow = SysTick->VAL;
		if (tnow != told)
		{
			if (tnow < told)
				tcnt += told - tnow;	//SysTick is a down counter
			else
				tcnt += reload - tnow + told;
			told = tnow;
			if (tcnt >= ticks)
				break;			//when the delay is due
		}
	};
}

/**
 * [delayMs description]
 * @param nms number of milliseconds, range[0,65535];
 */
void delayMs(uint16_t nms)
{
	uint64_t target;

	target = getTimeMillis() + nms;

	while (target > getTimeMillis())
		delayUs(100);

}

uint64_t getTimeMicros(void)
{
	uint32_t time;
	uint32_t millis;
	uint32_t reload = SysTick->LOAD; //get reload value

	DISABLE_SYSTICK_INTERRUPT();
	time = SysTick->VAL;
	millis = milliseconds;
	ENABLE_SYSTICK_INTERRUPT();
	
	return ((uint64_t) millis) * 1000 + (reload - time) / (CLOCK_FREQUENCY / 8);
}

uint64_t getTimeMillis(void)
{
	uint32_t millis;

	DISABLE_SYSTICK_INTERRUPT();
	millis = milliseconds;
	ENABLE_SYSTICK_INTERRUPT();

	return (uint64_t) millis;
}

void SysTick_Handler(void)
{
	milliseconds++;
}
































