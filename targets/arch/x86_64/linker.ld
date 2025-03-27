ENTRY(start)

SECTIONS
{
    /* Start at 1MB (0x100000), where most x86 kernels are loaded */
    . = 1M;

    /* Multiboot header must be in the first 8 KiB */
    .boot : ALIGN(4096) 
    {
        KEEP(*(.multiboot_header))
    }

    /* Code section */
    .text : ALIGN(4096) 
    {
        _text_start = .;
        *(.text .text.*)
        _text_end = .;
    }

    /* Read-only data */
    .rodata : ALIGN(4096)
    {
        _rodata_start = .;
        *(.rodata .rodata.*)
        _rodata_end = .;
    }

    /* Data section (initialized variables) */
    .data : ALIGN(4096) 
    {
        _data_start = .;
        *(.data .data.*)
        _data_end = .;
    }

    /* BSS (uninitialized data) */
    .bss : ALIGN(4096) 
    {
        _bss_start = .;
        *(.bss .bss.*)
        _bss_end = .;
    }

    /* Define BSS size for runtime clearing */
    _bss_size = _bss_end - _bss_start;

    /* Kernel Stack (16 KiB) */
    .stack : ALIGN(4096) 
    {
        _stack_start = .;
        . += 16K;
        _stack_end = .;
    }
}
