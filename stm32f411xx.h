/* STM32F411 Device Header File */
#ifndef STM32F411XX_H
#define STM32F411XX_H

#include <stdint.h>

/*----------------------------------------------------------
  Peripheral Base Addresses
  ----------------------------------------------------------*/
#define PERIPH_BASE (0x40000000UL)
#define AHB1PERIPH_BASE (PERIPH_BASE + 0x00020000UL)
#define APB1PERIPH_BASE (PERIPH_BASE + 0x00000000UL)
#define APB2PERIPH_BASE (PERIPH_BASE + 0x00010000UL)

/*----------------------------------------------------------
  Register Structures
  ----------------------------------------------------------*/
/* GPIO Structure */
typedef struct {
	volatile uint32_t MODER;	// GPIO mode register         Offset: 0x00
	volatile uint32_t OTYPER;	// Output type register        Offset: 0x04
	volatile uint32_t OSPEEDR;	// Output speed register       Offset: 0x08
	volatile uint32_t PUPDR;	// Pull-up/pull-down register  Offset: 0x0C
	volatile uint32_t IDR;		// Input data register         Offset: 0x10
	volatile uint32_t ODR;		// Output data register        Offset: 0x14
	volatile uint32_t BSRR;		// Bit set/reset register      Offset: 0x18
	volatile uint32_t LCKR;		// Configuration lock register Offset: 0x1C
	volatile uint32_t AFR[2];	// Alternate function registers Offset: 0x20-0x24
} GPIO_TypeDef;

/* RCC Structure */
typedef struct {
	volatile uint32_t CR;		 // Clock control register            Offset: 0x00
	volatile uint32_t PLLCFGR;	 // PLL configuration register        Offset: 0x04
	volatile uint32_t CFGR;		 // Clock configuration register      Offset: 0x08
	volatile uint32_t CIR;		 // Clock interrupt register          Offset: 0x0C
	volatile uint32_t AHB1RSTR;	 // AHB1 peripheral reset register    Offset: 0x10
	volatile uint32_t AHB2RSTR;	 // AHB2 peripheral reset register    Offset: 0x14
	uint32_t RESERVED0[2];		 // Reserved                          Offset: 0x18-0x1C
	volatile uint32_t APB1RSTR;	 // APB1 peripheral reset register    Offset: 0x20
	volatile uint32_t APB2RSTR;	 // APB2 peripheral reset register    Offset: 0x24
	uint32_t RESERVED1[2];		 // Reserved                          Offset: 0x28-0x2C
	volatile uint32_t AHB1ENR;	 // AHB1 peripheral clock enable      Offset: 0x30
	volatile uint32_t AHB2ENR;	 // AHB2 peripheral clock enable      Offset: 0x34
	uint32_t RESERVED2[2];		 // Reserved                          Offset: 0x38-0x3C
	volatile uint32_t APB1ENR;	 // APB1 peripheral clock enable      Offset: 0x40
	volatile uint32_t APB2ENR;	 // APB2 peripheral clock enable      Offset: 0x44
} RCC_TypeDef;

/* PWR Structure */
typedef struct {
	volatile uint32_t CR;	// Power control register           Offset: 0x00
	volatile uint32_t CSR;	// Power control/status register    Offset: 0x04
} PWR_TypeDef;

/* FLASH Structure */
typedef struct {
	volatile uint32_t ACR;		// Access control register         Offset: 0x00
	volatile uint32_t KEYR;		// Key register                    Offset: 0x04
	volatile uint32_t OPTKEYR;	// Option key register             Offset: 0x08
	volatile uint32_t SR;		// Status register                 Offset: 0x0C
	volatile uint32_t CR;		// Control register                Offset: 0x10
	volatile uint32_t OPTCR;	// Option control register         Offset: 0x14
} FLASH_TypeDef;

/* SysTick Structure */
typedef struct {
	volatile uint32_t CTRL;
	volatile uint32_t LOAD;
	volatile uint32_t VAL;
	volatile uint32_t CALIB;
} SysTick_Type;

/* Peripheral Instances */
#define GPIOA ((GPIO_TypeDef *)(AHB1PERIPH_BASE + 0x0000))
#define GPIOB ((GPIO_TypeDef *)(AHB1PERIPH_BASE + 0x0400))
#define GPIOC ((GPIO_TypeDef *)(AHB1PERIPH_BASE + 0x0800))
#define RCC ((RCC_TypeDef *)(AHB1PERIPH_BASE + 0x3800))
#define PWR ((PWR_TypeDef *)(APB1PERIPH_BASE + 0x7000))
#define FLASH ((FLASH_TypeDef *)(AHB1PERIPH_BASE + 0x3C00))
#define SysTick ((SysTick_Type *)0xE000E010UL)

/* GPIO Pin definitions */
#define GPIO_Pin_0 (1 << 0)
#define GPIO_Pin_1 (1 << 1)
#define GPIO_Pin_2 (1 << 2)
#define GPIO_Pin_3 (1 << 3)
#define GPIO_Pin_4 (1 << 4)
#define GPIO_Pin_5 (1 << 5)
#define GPIO_Pin_6 (1 << 6)
#define GPIO_Pin_7 (1 << 7)
#define GPIO_Pin_13 (1 << 13)

#endif /* STM32F411XX_H */
