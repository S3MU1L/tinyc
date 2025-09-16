int main()
{
    int i = -1;
    if ( i > 0 )
        assert( 0 );

    i = 0;
    assert( --i < 0 );

    i = 2;
    i -= 20u;

    assert( i < 0 );
    assert( ( i >>= 1 ) == -9 );
    assert( i == -9 );
    assert( ( i >> 2 ) == -3 );
    assert( i == -9 );

    signed char x = 0xf0;
    assert( ( x >> 2 ) == ( signed char ) 0xfc );

    unsigned char y = 0xf0;
    assert( ( y >> 2 ) == 0x3c );

    return 0;
}

