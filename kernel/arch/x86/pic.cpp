#include "arch/x86/pic.h"
#include "arch/x86/io.h"


//master pic command port.
const unsigned short pic_master_command = 0x20;
//master pic data port.
const unsigned short pic_master_data = 0x21;
//slave pic command port.
const unsigned short pic_slave_command = 0xA0;
//slave pic data port.
const unsigned short pic_slave_data = 0xA1;


void pic_init() {
    //start initialization on both pics.
    outb(pic_master_command, 0x11);
    outb(pic_slave_command, 0x11);

    //set the master pic interrupt vector offset.
    outb(pic_master_data, 0x20);

    //set the slave pic interrupt vector offset.
    outb(pic_slave_data, 0x28);

    //tell the master pic that the slave is connected to irq2.
    outb(pic_master_data, 0x04);

    //tell the slave pic that it is connected to irq2 on the master.
    outb(pic_slave_data, 0x02);

    //set both pics to 8086 mode.
    outb(pic_master_data, 0x01);
    outb(pic_slave_data, 0x01);

    //UNMASKING

    //keyboard interrupt.
    outb(pic_master_data, 0xFD);

    //mask all slave pic interrupts
    outb(pic_slave_data, 0xFF);
}


//signal that a hardware interrupt has been handled.
void pic_eoi(unsigned char irq) {

    //send an eoi to the slave pic if the irq came from the slave.
    if (irq >= 8) {
        outb(pic_slave_command, 0x20);
    }

    //send an eoi to the master pic.
    outb(pic_master_command, 0x20);
}


//verify that the programmable interrupt controller was initialized correctly.
bool pic_verify() {
    //read the master pic interrupt mask.
    unsigned char master_mask = inb(pic_master_data);
    //read the slave pic interrupt mask.
    unsigned char slave_mask = inb(pic_slave_data);

    //verify that only irq1 is enabled on the master and all slave irqs are masked.
    return master_mask == 0xFD
        && slave_mask == 0xFF;
}