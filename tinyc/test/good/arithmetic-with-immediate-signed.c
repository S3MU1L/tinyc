//#include<assert.h>
int main()
{
    int x = -10;

    assert(   x == -10 );
    assert( -10 ==   x );

    assert(  x != 10 );
    assert( 10 !=  x );

    assert(   x < -9 );
    assert( -11 <  x );

    assert(  x > -11 );
    assert( -9 >   x );

    assert(   x <=  -9 );
    assert( -11 <=   x );
    assert(   x <= -10 );
    assert( -10 <=   x );

    assert(   x >= -11 );
    assert(  -9 >=   x );
    assert(   x >= -10 );
    assert( -10 >=   x );

    assert( x + 1 == -9 );
    assert( 1 + x == -9 );

    assert(  x - 2 == -12 );
    assert( 13 - x ==  23 );

    assert( x * 3 == -30 );
    assert( 3 * x == -30 );

    assert(   x /  5 == -2 );
    assert(  50 /  x == -5 );
    assert(   x / -5 ==  2 );
    assert( -50 /  x ==  5 );

    assert(  x %  7 == -3 );
    assert(  7 %  x ==  7 );
    assert(  x % -7 == -3 );
    assert( -7 %  x == -7 );

    assert( ( x & 7 ) == 6 );
    assert( ( 7 & x ) == 6 );

    assert( ( x | 7 ) == -9 );
    assert( ( 7 | x ) == -9 );

    assert( ( x ^ 7 ) == -15 );
    assert( ( 7 ^ x ) == -15 );

    // UB: assert( x << 2 == -40 );

    assert( x >> 2 == -3 );

    x = 10;
    assert( x << 2 == 40 );

    return 0;
}
