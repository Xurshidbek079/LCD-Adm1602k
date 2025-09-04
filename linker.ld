/* Basic linker script for STM32F411CEU6 (512KB Flash, 128KB RAM) */
ENTRY(Reset_Handler)

MEMORY
{
  FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 512K
  RAM   (rwx) : ORIGIN = 0x20000000, LENGTH = 128K
}

_estack = ORIGIN(RAM) + LENGTH(RAM);  /* Stack grows down from top of RAM */

SECTIONS
{
  /* Interrupt vector table + startup code */
  .isr_vector :
  {
    KEEP(*(.isr_vector))
  } > FLASH

  /* Read-only code and data (text and consts) */
  .text :
  {
    *(.text*)           /* Program code */
    *(.rodata*)         /* Read-only data */
    _etext = .;         /* End of .text section (used to copy .data) */
  } > FLASH

  /* Initialized data (copied to RAM at runtime) */
  .data : AT(_etext)
  {
    _sdata = .;         /* Start of .data section in RAM */
    *(.data*)           /* Initialized data */
    _edata = .;         /* End of .data section */
  } > RAM

  /* Uninitialized data (zeroed at runtime) */
  .bss :
  {
    _sbss = .;          /* Start of .bss */
    *(.bss*)
    *(COMMON)
    _ebss = .;          /* End of .bss */
  } > RAM

  /* Stack top */
  . = ALIGN(4);
  _stack_top = _estack;
}
