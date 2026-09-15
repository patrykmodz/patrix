patrix - kernel made in c++.

version 0.09

============

UPDATE LOG:

v0.01 - bootable kernel

v0.02 - first character on screen

v0.03 - string output

v0.04 - newline handling

v0.05 - screen scrolling

v0.06 - right-edge handling

v0.07 - vga screen clearing

v0.08 - vga cursor control

v0.09 - gdt:
    - added gdt interface
    - added gdt implementation
    - added gdt flush assembly
    - loaded the gdt during kernel boot
    - reloaded kernel segment registers
    - verified that execution continues after gdt initialization