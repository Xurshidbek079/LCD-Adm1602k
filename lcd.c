/* HD44780 LCD Driver Implementation (4-bit Mode) */
#include "lcd.h"

#include "system.h"

/*----------------------------------------------------------
  Private Function Prototypes
  ----------------------------------------------------------*/
static void LCD_Configuration(void);
static inline void LCD_Pulse_E(void);
static inline void LCD_Send_Nibble(uint8_t nibble);
static inline void LCD_Delay(uint32_t count);

/*----------------------------------------------------------
  Private Functions
  ----------------------------------------------------------*/

/* Simple delay function (adjust for timing) */
static inline void LCD_Delay(uint32_t count) {
	volatile uint32_t i;
	for (i = 0; i < count * 10; i++) {
		__asm volatile("nop");
	}
}

/* GPIO Configuration for LCD (4-bit mode) */
static void LCD_Configuration(void) {
	// Enable GPIO clocks
	RCC->AHB1ENR |= (1 << 0) | (1 << 1);  // Enable GPIOA, GPIOB

	// Configure GPIOA pins: PA0=RS, PA1=RW, PA2=E (output)
	GPIOA->MODER &= ~((3 << (0 * 2)) | (3 << (1 * 2)) | (3 << (2 * 2)));
	GPIOA->MODER |= ((1 << (0 * 2)) | (1 << (1 * 2)) | (1 << (2 * 2)));	   // Output mode
	GPIOA->OSPEEDR |= ((3 << (0 * 2)) | (3 << (1 * 2)) | (3 << (2 * 2)));  // High speed

	// Configure GPIOB pins: PB4-PB7 for data (output)
	GPIOB->MODER &= ~(0x0000FF00);	// Clear mode bits for PB4-PB7
	GPIOB->MODER |= 0x00005500;		// Set PB4-PB7 as output
	GPIOB->OSPEEDR |= 0x0000FF00;	// High speed for PB4-PB7
}

/* Pulse E pin */
static inline void LCD_Pulse_E(void) {
	LCD_E_SET;
	delay_ms(1);  // Enable pulse width
	LCD_E_CLR;
	delay_ms(1);  // Hold time
}

/* Send 4-bit nibble */
static inline void LCD_Send_Nibble(uint8_t nibble) {
	// Write nibble to PB4-PB7
	LCD_DATA_PORT->ODR =
		(LCD_DATA_PORT->ODR & ~LCD_DATA_MASK) | ((nibble & 0x0F) << LCD_DATA_OFFSET);
	LCD_Pulse_E();
}

/*----------------------------------------------------------
  Public Functions
  ----------------------------------------------------------*/

/* Send command (RS=0) */
void LCD_Send_Command(uint8_t cmd) {
	LCD_RS_CLR;
	LCD_RW_CLR;
	LCD_Send_Nibble(cmd >> 4);	// High nibble
	LCD_Send_Nibble(cmd);		// Low nibble
	if (cmd == 0x01 || cmd == 0x02) {
		delay_ms(5);  // Clear/Home commands need more time
	} else {
		delay_ms(2);  // Standard command time
	}
}

/* Send data (RS=1) */
void LCD_Send_Data(uint8_t data) {
	LCD_RS_SET;
	LCD_RW_CLR;
	LCD_Send_Nibble(data >> 4);	 // High nibble
	LCD_Send_Nibble(data);		 // Low nibble
	delay_ms(1);				 // Data write time
}

/* Set cursor position */
void LCD_Set_Cursor(uint8_t row, uint8_t col) {
	uint8_t address = (row == 0) ? col : (0x40 + col);
	LCD_Send_Command(0x80 | address);
}

/* Print string */
void LCD_Print_String(const char* str) {
	while (*str) {
		LCD_Send_Data(*str++);
	}
}

/* Clear display */
void LCD_Clear(void) {
	LCD_Send_Command(0x01);	 // Clear command
	delay_ms(5);			 // Clear needs extra time
}

/* LCD Initialization (4-bit mode) */
void LCD_Initialization(void) {
	LCD_Configuration();  // Pin initialization

	// Initial states
	LCD_RS_CLR;
	LCD_RW_CLR;
	LCD_E_CLR;

	delay_ms(50);  // Power on delay

	// Initialization sequence for 4-bit mode (HD44780 datasheet)
	LCD_Send_Nibble(0x03);	// Function set
	delay_ms(5);
	LCD_Send_Nibble(0x03);	// Repeat
	delay_ms(1);
	LCD_Send_Nibble(0x03);	// Repeat
	delay_ms(1);
	LCD_Send_Nibble(0x02);	// Set 4-bit mode
	delay_ms(1);

	// Now use full commands
	LCD_Send_Command(0x28);	 // Function set: 4-bit, 2-line, 5x8 font
	LCD_Send_Command(0x08);	 // Display off
	LCD_Send_Command(0x01);	 // Clear display
	LCD_Send_Command(0x06);	 // Entry mode: increment, no shift
	LCD_Send_Command(0x0C);	 // Display on, cursor off, blink off
}
