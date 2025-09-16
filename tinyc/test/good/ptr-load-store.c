int main()
{
    int x = 42;
    int y = 66;
    assert( x == 42 );
    assert( y == 66 );

    int *px = &x,
        *py = &y;

    assert( *px == 42 );
    assert( *py == 66 );

    y = 100;
    *py = ( *px = *py ) + 20;

    assert( x == 100 );
    assert( y == 120 );

    *px += ( *py += *px );

    assert( y == 220 );
    assert( x == 320 );

    return 0;
}
