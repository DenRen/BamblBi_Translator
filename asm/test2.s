global _start

%include "mystdmacro.s"
%include "mystdlib.s"
%include "utests.s"

name_   db "Ded", 0x0
msg1 db "Hss", 0x0
str_love db "love", 0x0
section .text

_start:
    prog_start

    nop
    nop
    nop

    push 15
    push "!"
    push 100
    push 3208
    push str_love
    push ded_

    call printf__

    sub sp, 6 * 8


;---------------------------
;          DEBUG
;---------------------------
;   call utests_
;---------------------------

    nop
    nop
    nop

    prog_finish
_L_:
    prog_finish

section .rodata

orig_   db "Hello, %s! As you said, the number %d is one of the most important in a student?s life. It can be derived in all calculus systems:", brkl, "BIN: %b", brkl, "OCT: %o", brkl, "HEX: %x", brkl, "But everyone will recognize him anyway)", brkl, 0x0