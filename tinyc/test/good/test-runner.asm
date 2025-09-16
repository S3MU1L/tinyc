main:
    ld   l7, data   → l6
    eq   l6, 0xffff → t1 ; test-end marker
    jz   t1, solution
    ret

data:   ; input, expect
    .word     1,      2
    .word     5,     10
    .word   128,    256
    .word    20,     40
    .word    -1,      0

check:
    add  l7, 2      → l7
    ld   l7, data   → t1
    eq   rv, t1     → t1
    asrt t1
    add  l7, 2      → l7
    jmp  main

.trigger set _tc_expect_ 4
.trigger inc _tc_

solution:
    add  l6, l6 -> rv
    jmp  check
