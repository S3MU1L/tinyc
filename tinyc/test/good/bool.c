int main()
{
    assert( !false );
    assert( true );
    assert( true + true == 2 );

    bool x = 42;
    &x;

    assert( x );
    assert( x == 1 );
    assert( !x == 0 );
    assert( ( x || x ) == 1 );
    assert( ( x && x ) == 1 );

    int y = 42;
    x = y;

    assert( x );
    assert( x == 1 );
    assert( !x == 0 );
    assert( ( x || x ) == 1 );
    assert( ( x && x ) == 1 );

    return 0;
}

