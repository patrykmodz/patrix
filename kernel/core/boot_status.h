#pragma once

//describe the result of a boot initialization step.
enum class BootStatus {
    OK,
    WARNING,
    FAILED
};

//display the result of a boot initialization step.
void boot_status(BootStatus status, const char* name);