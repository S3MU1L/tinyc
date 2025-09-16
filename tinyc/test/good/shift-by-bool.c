bool boolify( int x ) { return x; }
bool gettrue1() { return 4; }
bool gettrue2() { int x = 4; return x; }

int main()
{
    int x = 1;
    int y = 3;
    int z = 4;

    x <<= ( y || z );
    assert( x == 2 );
    x <<= ( y && z );
    assert( x == 4 );
    x <<= ( ( bool ) y );
    assert( x == 8 );
    x <<= ( !y );

    x <<= ( 4 || z );
    assert( x == 16 );
    x <<= ( y || 3 );
    assert( x == 32 );
    x <<= ( 4 || 3 );
    assert( x == 64 );

    x >>= ( 3 && z );
    assert( x == 32 );
    x >>= ( y && 4 );
    assert( x == 16 );
    x >>= ( 3 && 4 );
    assert( x == 8 );

    x >>= ( ( bool ) 4 );
    assert( x == 4 );
    x >>= ( !4 );
    assert( x == 4 );

    bool b = 5;
    x >>= b;
    assert( x == 2 );

    x >>= boolify( 4 );
    assert( x == 1 );
    x <<= gettrue1();
    assert( x == 2 );
    x <<= gettrue2();
    assert( x == 4 );

    return 0;
}
