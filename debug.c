/* Debug LED Control Implementation */
#include "debug.h"

/*----------------------------------------------------------
  Debug LED Functions
  ----------------------------------------------------------*/

/* Initialize Debug LED (PC13) */
void Debug_LED_Init(void) {
	// Enable GPIOC clock
	RCC->AHB1ENR |= (1 << 2);  // Enable GPIOC

	// Configure GPIOC pin: PC13 as output for debug LED
	GPIOC->MODER &= ~(3 << (13 * 2));
	GPIOC->MODER |= (1 << (13 * 2));	// Output mode
	GPIOC->OSPEEDR |= (3 << (13 * 2));	// High speed
	DEBUG_LED_CLR;						// Start with LED off
}

/* Turn on Debug LED */
void Debug_LED_On(void) { DEBUG_LED_SET; }

/* Turn off Debug LED */
void Debug_LED_Off(void) { DEBUG_LED_CLR; }

/* Toggle Debug LED */
void Debug_LED_Toggle(void) { DEBUG_LED_TOGGLE; }
