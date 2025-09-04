/* Main Application */
#include "debug.h"
#include "lcd.h"
#include "system.h"

/*----------------------------------------------------------
   Main Application
   ----------------------------------------------------------*/
int main(void) {
	// System initialization
	SysClockConfig();
	systick_init();

	// Peripheral initialization
	Debug_LED_Init();
	LCD_Initialization();

	// Clear display first
	LCD_Clear();

	// Display messages
	LCD_Set_Cursor(0, 0);  // First line, position 0
	LCD_Print_String("hello");

	LCD_Set_Cursor(1, 0);  // Second line, position 0
	LCD_Print_String("world!");

	/* Infinite loop with status indication */
	while (1) {
		// Toggle LED to indicate program is running
		Debug_LED_Toggle();
		delay_ms(1000);
	}
}
