
section .multiboot_header

header_start:
    ; Magic Number
    dd 0xe85250d6 ; multiboot2 magic number

    ; Architecture
    dd 0x00000000 ; protectecd mode

    ; Header Length
    dd header_end - header_start

    ; Checksum
    dd 0x100000000 - (0xe85250d6 + 0x00000000 + (header_end - header_start))
    
    ; End tag
    dw 0
    dw 0
    dd 8
header_end: