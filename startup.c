/* STM32F411 Startup Code and Vector Table */
#include "system.h"

/*----------------------------------------------------------
  Interrupt Vector Table
  ----------------------------------------------------------*/
__attribute__((section(".isr_vector"))) void (*const vector_table[])(void) = {
	(void (*)(void))(&_stack_top),	// Stack top pointer
	Reset_Handler,					// Reset Handler
	Default_Handler,				// NMI
	Default_Handler,				// Hard Fault
	Default_Handler,				// Memory Management Fault
	Default_Handler,				// Bus Fault
	Default_Handler,				// Usage Fault
	0, 0, 0, 0,						// Reserved
	Default_Handler,				// SVCall
	Default_Handler,				// Debug Monitor
	0,								// Reserved
	Default_Handler,				// PendSV
	SysTick_Handler,				// SysTick
	// Additional peripheral interrupts can be added here
};
