patrix - kernel made in c++.

version 0.12.2

============

UPDATE LOG:

v0.12 - programmable interrupt controller + keyboard driver<br>
- added programmable interrupt controller initialization and verification<br>
- added interrupt end-of-interrupt handling<br>
- added basic keyboard driver and keyboard interrupt handling<br>
- added keyboard scancode definitions<br>
- enabled hardware interrupts after interrupt initialization<br>
- added basic key handling and keyboard input testing<br>

0.12.1 - colour!
- kernel panic is now blue and has a dedicated screen<br>
- "OK", "WARN", "FAIL" boot initialiser statuses are able to show green, yellow, and red for its corresponding status<br>
- some code clean-up (somewhere, probably)<br>

0.12.2 - fix failed boot status returning to kernel entry point<br>