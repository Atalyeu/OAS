kernel_source_files := $(shell find kernel -name *.c)
kernel_object_files := $(patsubst kernel/%.c, build/kernel/%.o, $(kernel_source_files))

x86_64_c_source_files := $(shell find arch/x86_64 -name *.c)
x86_64_c_object_files := $(patsubst arch/x86_64/%.c, build/arch/x86_64/%.o, $(x86_64_c_source_files))

x86_64_asm_source_files := $(shell find arch/x86_64 -name *.asm)
x86_64_asm_object_files := $(patsubst arch/x86_64/%.asm, build/arch/x86_64/%.o, $(x86_64_asm_source_files))

x86_64_object_files := $(x86_64_c_object_files) $(x86_64_asm_object_files)

$(x86_64_c_object_files): build/arch/x86_64/%.o : arch/x86_64/%.c
	mkdir -p $(dir $@) && \
	x86_64-elf-gcc -c -I ./include -ffreestanding -Wall -Wextra $(patsubst build/arch/x86_64/%.o, arch/x86_64/%.c, $@) -o $@  


$(kernel_object_files): build/kernel/%.o : kernel/%.c
	mkdir -p $(dir $@) && \
	x86_64-elf-gcc -c -I ./include -ffreestanding -Wall -Wextra $(patsubst build/kernel/%.o, kernel/%.c, $@) -o $@ 

$(x86_64_asm_object_files): build/x86_64/%.o : x86_64/%.asm
	mkdir -p $(dir $@) && \
	nasm -f elf64 $(patsubst build/arch/x86_64/%.o, arch/x86_64/%.asm, $@) -o $@

.PHONY: build-x86_64
build-x86_64: $(kernel_object_files) $(x86_64_object_files)
	mkdir -p dist/arch/x86_64 && \
	x86_64-elf-ld -n -o dist/arch/x86_64/kernel.bin -T targets/arch/x86_64/linker.ld $(kernel_object_files) $(x86_64_object_files) && \
	cp dist/arch/x86_64/kernel.bin targets/arch/x86_64/iso/boot/kernel.bin && \
	grub-mkrescue /usr/lib/grub/i386-pc -o dist/arch/x86_64/kernel.iso targets/arch/x86_64/iso