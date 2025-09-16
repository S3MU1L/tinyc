int main()
{
    int x = 15;

    assert( x + 0 == x );
    assert( 0 + x == x );
    assert( x - 0 == x );
    assert( 0 - x == -15 );

    assert( x * 1 == x );
    assert( 1 * x == x );
    assert( x / 1 == x );
    assert( 1 / x == 0 );

    assert( ( x | 0 ) == x );
    assert( ( 0 | x ) == x );
    assert( ( x ^ 0 ) == x );
    assert( ( 0 ^ x ) == x );
    assert( ( x & -1 ) == x );
    assert( ( -1 & x ) == x );

    assert( ( x << 0 ) == x );
    assert( ( x >> 0 ) == x );
    assert( ( 0 << x ) == 0 );
    assert( ( 0 >> x ) == 0 );

    return 0;
}
