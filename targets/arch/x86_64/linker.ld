ENTRY(start)

SECTIONS
{
    /* 
    ALIGN(4096) is aligment by the sections themselves
    Specify the alignment of each section within the executable image.
    */
    . = 1M;
    .boot : ALIGN(4096) /* Alinged by 16 bytes */
    {
        KEEP(*(.multiboot_header))
    }

    .text : ALIGN(4096) /* Alinged by 16 bytes */
    {
        _text_start = .;
        *(.text)
        _text_end = .;
    }

    .data : ALIGN(4096) /* Alinged by 16 bytes */ 
    {
        _data_start = .;
        *(.data)
        _data_end = .;
    }

    .bss : ALIGN(4096) /* Alinged by 16 bytes */
    {
        _bss_start = .;
        *(.bss)
        _bss_end = .;
    }

    .rodata : ALIGN(4096) /* Alinged by 16 bytes */
    {
        _rodata_start = .;
        *(.rodata)
        _rodata_end = .;
    }

    .stack : ALIGN(4096) /* Alinged by 16 bytes */
    {
        _stack_start = .;
        . += 16K; /* Reserve 16 KiB for the stack */
        _stack_end = .;
    }
}