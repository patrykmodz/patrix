#pragma once

enum key_modifier{
    BASE,
    SHIFT,
    ALTGR,
    SHIFT_ALTGR
};

/*
CHARACTER produces a character
MODIFIER changes how other keys behave
FUNCTION F1–F12
SPECIAL Enter, Backspace, Escape, Tab, etc.
EXTENDED keys you're choosing to classify separately, such as arrows/navigation keys
*/

enum key_type {
    CHARACTER,
    MODIFIER,
    FUNCTION,
    SPECIAL,
    EXTENDED
};

struct KEY {
    key_type type;
    key_modifier modifier;
    unsigned short scancode;
    char output;
};