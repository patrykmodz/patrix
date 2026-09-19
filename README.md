patrix - kernel made in c++.

version 0.14.0

============

UPDATE LOG:

v0.14.0 — console and boot initialization improvements<br>

- added `vgacon` console layer with cursor tracking<br>
- added console character and string output<br>
- added newline, line wrapping, and screen scrolling support<br>
- added console backspace support<br>
- added console initialization and verification<br>
- added console screen clearing and cursor reset<br>
- improved PIC initialization and verification<br>
- fixed PIC boot verification to use `pic_verify()`<br>
- added slave PIC interrupt masking<br>