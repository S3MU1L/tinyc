int main()
{
    int x = 3;
    int y = 0;

    while ( x > 0 )
    {
        int inner;
        x -= 1;
        y += 1;
    }

    assert( x == 0 );
    assert( y == 3 );

    for ( x = 3; x > 0; x -= 1 )
    {
        int inner = 1;
        y *= 2;
    }

    assert( x == 0 );
    assert( y == 24 );

    for ( int i = 0; i < 2; i += 1 )
    {
        y -= 2;
    }

    assert( x == 0 );
    assert( y == 20 );

    do {
        assert( x == 0 );
        y -= 1;
    }
    while( ( x += 2, 0 ) );

    assert( x == 2 );
    assert( y == 19 );

    for ( int x = 2; x > 0; )
    {
        x -= 1;
        y -= 1;
    }

    assert( x == 2 );
    assert( y == 17 );

    for ( ; x > 0; )
    {
        x -= 1;
        y -= 1;
    }

    assert( x == 0 );
    assert( y == 15 );

    return 0;
}
