MEMORY
{
  rom (rx)  : ORIGIN = 0x08000000, LENGTH = 512K
  ram (rwx) : ORIGIN = 0x20000000, LENGTH = 96K
}

ENTRY(reset_handler)

SECTIONS
{
  .text : {
    KEEP(*(.vectors))
    *(.text*)
    *(.rodata*)
    . = ALIGN(4);
    _etext = .;
  } >rom

  .data : {
    _data = .;
    *(.data*)
    . = ALIGN(4);
    _edata = .;
  } >ram AT >rom
  _data_loadaddr = LOADADDR(.data);

  .bss : {
    _bss = .;
    *(.bss*)
    *(COMMON)
    . = ALIGN(4);
    _ebss = .;
  } >ram

  .rodata_inf : {
    . = ALIGN(4);
    __rodata_inf_start = .;
    LONG(0x7F800000)   /* +INF */
    LONG(0xFF800000)   /* -INF */
    __rodata_inf_end = .;
} >rom

}

PROVIDE(_stack = ORIGIN(ram) + LENGTH(ram));
PROVIDE(INF_addr = __rodata_inf_start);
PROVIDE(NEG_INF_addr = __rodata_inf_start + 4);
