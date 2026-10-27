ENTRY(_rom_entry)
MEMORY {
 ROM (rx) : ORIGIN = 0x08000000, LENGTH = 32M
 RAM (rw) : ORIGIN = 0x02000000, LENGTH = 256K
}
SECTIONS {
 .header : {KEEP(*(.header))} > ROM
 .text : ALIGN(4) {*(.text.startup) *(.text .text.*) KEEP(*(.rodata.save_id)) *(.rodata .rodata.*) . = ALIGN(4);} > ROM
 .ARM.exidx : {*(.ARM.exidx*)} > ROM
 .data : ALIGN(4) {__data_start = .; *(.data .data.*) . = ALIGN(4); __data_end = .;} > RAM AT> ROM
 __data_load = LOADADDR(.data);
 .bss (NOLOAD) : ALIGN(4) {__bss_start = .; *(.bss .bss.*) *(COMMON) . = ALIGN(4); __bss_end = .;} > RAM
 /DISCARD/ : {*(.comment) *(.note*) *(.ARM.attributes)}
}
ASSERT(SIZEOF(.header)==192,"Bad cartridge header")
ASSERT(__bss_end<=0x02040000,"EWRAM overflow")
