int b2i( bool x ) { return x; }
bool b2b( bool x ) { return x; }
bool b2b2( bool x ) { return x && 12; }
bool i2b( int x ) { return x; }

int main()
{
    int x = 42;

    assert( x );
    assert( !!x );

    assert( !x == 0 );
    assert( !!x == 1 );

    assert( x != true );
    assert( x != false );
    assert( !x == false );
    assert( !!x == true );

    assert( ( x && 3 ) == 1 );
    assert( ( !x && 3 ) == 0 );
    assert( ( x || 3 ) == 1 );
    assert( ( !x || 3 ) == 1 );

    assert( ( 3 && x ) == 1 );
    assert( ( 3 && !x ) == 0 );
    assert( ( 0 || x ) == 1 );
    assert( ( 0 || !x ) == 0 );

    assert( b2i( x ) == 1 );
    assert( i2b( x ) == 1 );
    assert( b2b( x ) == 1 );
    assert( b2b2( x ) == 1 );

    assert( b2i( !x ) == 0 );
    assert( i2b( !x ) == 0 );
    assert( b2b( !x ) == 0 );
    assert( b2b2( !x ) == 0 );

    assert( b2i( x && x ) == 1 );
    assert( i2b( x || x ) == 1 );

    return 0;
}
