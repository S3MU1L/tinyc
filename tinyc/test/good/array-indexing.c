int main()
{
    int a[ 2 ];
    a[ 0 ] = 42;
    a[ 1 ] = 66;

    assert( *a == 42 );
    assert( *( a + 1 ) == 66 );

    assert( a[ 0 ] == 42 );
    assert( a[ 1 ] == 66 );

    int *p = a;
    assert( *p == 42 );
    assert( p[ 0 ] == 42 );
    assert( p[ 1 ] == 66 );

    assert( p + 1 == a + 1 );
    assert( p + 1 == &a[ 1 ] );

    int i = 0;
    assert( a[ i++ ] == 42 );
    assert( a[ i ] == 66 );

    assert( p[ --i ] == 42 );
    assert( p[ ++i ] == 66 );

    return 0;
}
