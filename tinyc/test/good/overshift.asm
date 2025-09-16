main:
    put  16, l1

loop:
    put  0x8000, l2
    shr  l2, l1, l2
    eq   l2, 0, l2
    asrt l2

    put  0x8000, l2
    sar  l2, l1, l2
    eq   l2, 0xffff, l2
    asrt l2

    put  0x0001, l2
    shl  l2, l1, l2
    eq   l2, 0, l2
    asrt l2

    eq   l1, 16, t1
    put  0x0101, l1
    jnz  t1, loop

    put  0, rv
    ret
