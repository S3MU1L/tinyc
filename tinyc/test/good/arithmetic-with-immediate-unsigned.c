int main()
{
    unsigned x = 10;

    assert(  x == 10 );
    assert( 10 ==  x );

    assert( x != 9 );
    assert( 9 != x );

    assert( x < 11 );
    assert( 9 <  x );

    assert(  x > 9 );
    assert( 11 > x );

    assert(  x <= 11 );
    assert(  9 <=  x );
    assert(  x <= 10 );
    assert( 10 <=  x );

    assert(  x >=  9 );
    assert( 11 >=  x );
    assert(  x >= 10 );
    assert( 10 >=  x );

    assert( x + 1 == 11 );
    assert( 1 + x == 11 );

    assert(  x - 2 == 8 );
    assert( 13 - x == 3 );

    assert( x * 3 == 30 );
    assert( 3 * x == 30 );

    assert( x / 5 == 2 );
    assert( 5 / x == 0 );

    assert( x % 7 == 3 );
    assert( 7 % x == 7 );

    assert( ( x & 7 ) == 2 );
    assert( ( 7 & x ) == 2 );

    assert( ( x | 7 ) == 15 );
    assert( ( 7 | x ) == 15 );

    assert( ( x ^ 7 ) == 13 );
    assert( ( 7 ^ x ) == 13 );

    assert( x << 2 ==   40 );
    assert( 2 << x == 2048 );

    assert(    x >> 2 == 2 );
    assert( 2048 >> x == 2 );

    return 0;
}
