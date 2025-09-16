int main()
{
    unsigned a = 5, b = 0, c = 0, d = 0,
             e = 4, f = 0, g = 0, h = 0,
             i = 8, j = 0, k = 0, l = 0,
             m = 0, n = 0, o = 0, p = 0,
             q = 0, r = 0, s = 0, t = 0,
             u = 0, v = 0, w = 2, x = 6;

    assert( x == 6 );
    x = a + e;
    assert( x == 9 );

    for ( unsigned i = 0; i < x; ++i ) { w += 1; }

    assert( x == 9 );
    assert( w == 11 );

    return 0;
}
