/* System Configuration and Timing Header */
#ifndef SYSTEM_H
#define SYSTEM_H

#include "stm32f411xx.h"

/*----------------------------------------------------------
  Memory Section Symbols (From Linker Script)
  ----------------------------------------------------------*/
extern uint32_t _etext;		 // End of .text (FLASH)
extern uint32_t _sdata;		 // Start of .data (RAM)
extern uint32_t _edata;		 // End of .data (RAM)
extern uint32_t _sbss;		 // Start of .bss (RAM)
extern uint32_t _ebss;		 // End of .bss (RAM)
extern uint32_t _stack_top;	 // Stack top

/*----------------------------------------------------------
  Function Prototypes
  ----------------------------------------------------------*/
void Reset_Handler(void);
void Default_Handler(void);
void SysTick_Handler(void);

/* System Clock Configuration */
void SysClockConfig(void);

/* SysTick Timer Functions */
void systick_init(void);
void delay_ms(uint32_t ms);

/* Global variable for system tick counter */
extern volatile uint32_t systick_ms;

#endif /* SYSTEM_H */
