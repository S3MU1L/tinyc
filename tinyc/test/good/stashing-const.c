int foo( const int *p )
{
    int x = 2;
    int y = 1;
    int z = 0;
    return y * p[ z ] / x;
}

int main()
{
    const int x = 42,
              y = 66,
              *p = &x;

    assert( foo( &x ) == 21 );

    assert( *p == 42 );
    assert( x == 42 );
    assert( y == 66 );
    assert( x == 42 );

    return 0;
}
