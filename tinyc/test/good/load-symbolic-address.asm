    .word 0xffff, 0xffff
data:
    .word 0x1234, 0x5678
    .word 0xffff, 0xffff

main:
    put  0 → t1
    ld   t1, data → l1
    eq   l1, 0x1234 → t2
    asrt t2
    ldb  t1, data → l1
    eq   l1, 0x0012 → t2
    asrt t2

    put  1, t1
    ld   t1, data, l1
    eq   l1, 0x3456, t2
    asrt t2
    ldb  t1, data, l1
    eq   l1, 0x0034, t2
    asrt t2

    put  2 -> t1
    ld   t1, data -> l1
    eq   l1, 0x5678 -> t2
    asrt t2
    ldb  t1, data -> l1
    eq   l1, 0x0056 -> t2
    asrt t2

    ret
