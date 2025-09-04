/* Debug LED Control Header */
#ifndef DEBUG_H
#define DEBUG_H

#include "stm32f411xx.h"

/*----------------------------------------------------------
  Debug LED Configuration
  ----------------------------------------------------------*/
// Debug LED on PC13
#define DEBUG_LED_SET GPIOC->BSRR = GPIO_Pin_13
#define DEBUG_LED_CLR GPIOC->BSRR = (GPIO_Pin_13 << 16)
#define DEBUG_LED_TOGGLE            \
	if (GPIOC->ODR & GPIO_Pin_13) { \
		DEBUG_LED_CLR;              \
	} else {                        \
		DEBUG_LED_SET;              \
	}

/*----------------------------------------------------------
  Function Prototypes
  ----------------------------------------------------------*/
void Debug_LED_Init(void);
void Debug_LED_On(void);
void Debug_LED_Off(void);
void Debug_LED_Toggle(void);

#endif /* DEBUG_H */
