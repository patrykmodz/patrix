#pragma once

//halt the kernel after an unrecoverable error.
[[noreturn]] void kernel_panic(const char* reason);