.section .text

.global gdt_flush

gdt_flush:
    #load the address of the gdt pointer into the eax register.
    mov 4(%esp), %eax
    #load the gdt pointer into the gdtr register.
    lgdt (%eax)
    #load the kernel data segment selector into the ax register.
    mov $0x10, %ax
    #load the kernel data segment into the data segment register.
    mov %ax, %ds
    #load the kernel data segment into the extra segment register.
    mov %ax, %es
    #load the kernel data segment into the fs segment register.
    mov %ax, %fs
    #load the kernel data segment into the gs segment register.
    mov %ax, %gs
    #load the kernel data segment into the stack segment register.
    mov %ax, %ss
    #perform a far jump to reload the code segment register.
    ljmp $0x08, $flush

flush:
    #return to the function that called gdt_flush.
    ret