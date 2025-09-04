/* System Configuration and Timing Implementation */
#include "system.h"

/* Global variable for system tick counter */
volatile uint32_t systick_ms = 0;

/*----------------------------------------------------------
  SysTick Timer Implementation
  ----------------------------------------------------------*/
void SysTick_Handler(void) { systick_ms++; }

void systick_init(void) {
	SysTick->LOAD = 50000 - 1;	// 1ms tick at 50 MHz
	SysTick->VAL = 0;			// Clear current value
	SysTick->CTRL = 0x7;		// Enable counter, interrupt, and use processor clock
}

void delay_ms(uint32_t ms) {
	uint32_t start = systick_ms;
	while ((systick_ms - start) < ms);
}

/*----------------------------------------------------------
  System Clock Configuration
  ----------------------------------------------------------*/
void SysClockConfig(void) {
	// 1. Enable HSE oscillator (assuming 25 MHz external crystal)
	RCC->CR |= (1 << 16);			 // RCC_CR_HSEON
	while (!(RCC->CR & (1 << 17)));	 // Wait for HSE to be ready (RCC_CR_HSERDY)

	// 2. Configure voltage regulator (High performance mode)
	RCC->APB1ENR |= (1 << 28);	// Enable power interface clock (RCC_APB1ENR_PWREN)
	PWR->CR |= (3 << 14);		// Set VOS scale 1 (PWR_CR_VOS)

	// 3. Set Flash wait states and enable cache
	FLASH->ACR = (1 << 8) |	  // Instruction cache enable (FLASH_ACR_ICEN)
				 (1 << 9) |	  // Data cache enable (FLASH_ACR_DCEN)
				 (1 << 10) |  // Prefetch enable (FLASH_ACR_PRFTEN)
				 (1 << 0);	  // 1 wait state for 50 MHz (FLASH_ACR_LATENCY_1WS)

	// 4. Configure Prescalers
	RCC->CFGR |= (0 << 4);	 // AHB Prescaler: /1 => HCLK = SYSCLK = 50 MHz
	RCC->CFGR |= (4 << 10);	 // APB1 Prescaler: /2 => PCLK1 = 25 MHz
	RCC->CFGR |= (0 << 13);	 // APB2 Prescaler: /1 => PCLK2 = 50 MHz

	// 5. Configure PLL for 50MHz: HSE(25MHz) / 25 * 100 / 2 = 50MHz
	RCC->PLLCFGR = (25 << 0) |	 // PLL_M = 25
				   (100 << 6) |	 // PLL_N = 100
				   (0 << 16) |	 // PLL_P = 2 (00)
				   (1 << 22);	 // PLL source = HSE

	// 6. Enable PLL
	RCC->CR |= (1 << 24);			 // RCC_CR_PLLON
	while (!(RCC->CR & (1 << 25)));	 // Wait till PLL is ready (RCC_CR_PLLRDY)

	// 7. Switch system clock to PLL
	RCC->CFGR |= (2 << 0);						 // RCC_CFGR_SW: Select PLL as SYSCLK
	while ((RCC->CFGR & (3 << 2)) != (2 << 2));	 // Wait for PLL to be used as SYSCLK
}

/*----------------------------------------------------------
  Reset Handler
  ----------------------------------------------------------*/
void Reset_Handler(void) {
	// 1. Copy data section from FLASH to RAM
	uint32_t *src = &_etext;
	uint32_t *dst = &_sdata;
	while (dst < &_edata) *dst++ = *src++;

	// 2. Zero-fill .bss section
	dst = &_sbss;
	while (dst < &_ebss) *dst++ = 0;

	// 3. Call main()
	extern int main(void);
	main();

	// 4. Loop forever if main returns
	while (1);
}

/*----------------------------------------------------------
  Default Exception Handler
  ----------------------------------------------------------*/
void Default_Handler(void) { while (1); }
