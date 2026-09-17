#pragma once

//initialize the programmable interrupt controller.
void pic_init();
//signal that a hardware interrupt has been handled.
void pic_eoi(unsigned char irq);