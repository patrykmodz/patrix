#pragma once

//describe one entry in the interrupt descriptor table.
struct __attribute__((packed)) IDTEntry {
    unsigned short base_low;
    unsigned short selector;
    unsigned char zero;
    unsigned char flags;
    unsigned short base_high;
};

//describe the location and size of the interrupt descriptor table.
struct __attribute__((packed)) IDTPointer {
    unsigned short limit;
    unsigned int base;
};

//store the processor state passed to the common interrupt handler.
struct InterruptFrame {

    unsigned int edi;               //destination index register.
    unsigned int esi;               //source index register.
    unsigned int ebp;               //base pointer register.
    unsigned int original_esp;      //stack pointer before pusha was executed.
    unsigned int ebx;               //base register.
    unsigned int edx;               //data register.
    unsigned int ecx;               //counter register.
    unsigned int eax;               //accumulator register.

    unsigned int interrupt_number;  //interrupt vector number.
    unsigned int error_code;        //error code supplied by the cpu or created by the stub.

    unsigned int eip;               //instruction pointer at the time of the interrupt.
    unsigned int cs;                //code segment selector at the time of the interrupt.
    unsigned int eflags;            //processor flags at the time of the interrupt.
};

//initialize the interrupt descriptor table.
void idt_init();

//handle interrupt vector 0 in assembly.
extern "C" void interrupt_stub_0();

//verify that the interrupt descriptor table was loaded correctly.
bool idt_verify();

//load the interrupt descriptor table.
extern "C" void idt_flush(unsigned int pointer);

//initialize the first interrupt vector.
void idt_test_init();

//handle the test interrupt.
extern "C" void idt_test_handler();

//handle interrupts after the assembly stub has saved the processor state.
extern "C" void interrupt_handler(InterruptFrame* frame);