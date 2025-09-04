/* HD44780 LCD Driver Header (4-bit Mode) */
#ifndef LCD_H
#define LCD_H

#include "stm32f411xx.h"

/*----------------------------------------------------------
  LCD Configuration Defines
  ----------------------------------------------------------*/
// Control pin macros - Using GPIOA pins
#define LCD_RS_SET GPIOA->BSRR = GPIO_Pin_0			 // RS=1 (PA0)
#define LCD_RS_CLR GPIOA->BSRR = (GPIO_Pin_0 << 16)	 // RS=0

#define LCD_RW_SET GPIOA->BSRR = GPIO_Pin_1			 // RW=1 (PA1)
#define LCD_RW_CLR GPIOA->BSRR = (GPIO_Pin_1 << 16)	 // RW=0

#define LCD_E_SET GPIOA->BSRR = GPIO_Pin_2			// E=1 (PA2)
#define LCD_E_CLR GPIOA->BSRR = (GPIO_Pin_2 << 16)	// E=0

// Data pins: PB4-PB7 for DB4-DB7 (4-bit mode)
#define LCD_DATA_PORT GPIOB
#define LCD_DATA_OFFSET 4	  // Starting at PB4
#define LCD_DATA_MASK 0x00F0  // Bits 4-7

/*----------------------------------------------------------
  Public Function Prototypes
  ----------------------------------------------------------*/
/* LCD Initialization */
void LCD_Initialization(void);

/* Basic LCD Operations */
void LCD_Clear(void);
void LCD_Set_Cursor(uint8_t row, uint8_t col);
void LCD_Print_String(const char* str);

/* Low-level LCD Functions */
void LCD_Send_Command(uint8_t cmd);
void LCD_Send_Data(uint8_t data);

#endif /* LCD_H */
