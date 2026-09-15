# multiboot header.
.set ALIGN, 1<<0                    # request alignment
.set MEMINFO, 1<<1                  # request memory information
.set FLAGS, ALIGN | MEMINFO         # combine those requests
.set MAGIC, 0x1BADB002              # identifies the header as a Multiboot header
.set CHECKSUM, -(MAGIC + FLAGS)     # verification value. magic + flags + checksum must equal 0

# puts the following data into a section called .multiboot.
.section .multiboot
# the following data should start at an address aligned to 4 bytes.
.align 4

# store these values as a 32-bit integer (4 bytes).
.long MAGIC
.long FLAGS
.long CHECKSUM



# kernel code.
# .text is the section where executable machine code/instructions go.
.section .text
# linker needs to be able to identify _start as the kernel's entry point.
.global _start
# kernel_main exists somewhere.
.extern kernel_main

_start:
    cli                     # clear interrupt flag
    mov $stack_top, %esp    # set esp to the top of our reserved kernel stack.
    call kernel_main        # enter the kernel.

# simple halt.
halt:
    hlt
    jmp halt

# stack
# section for uninitialized data.
.section .bss

# following data starts at an address aligned to 16 bytes.
.align 16

stack_bottom: # bottom of the reserved stack area.
    # reserve 16,384 bytes of space without putting actual data there.
    .skip 16384
stack_top: # marks the other end of that reserved region.
