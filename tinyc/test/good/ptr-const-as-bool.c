bool p2b( const int *p ) { return p; }
bool b()
{
    const int x;
    return &x;
}

int main()
{
    int x;
    const int *p = &x;

    assert( p );
    assert( !p == 0 );
    assert( !!p );
    assert( !!p == 1 );

    if ( p )
        assert( true );
    if ( !p )
        assert( false );

    if ( p == 0 )
        assert( false );
    if ( p != 0 )
        assert( true );

    assert( p2b( p ) == 1 );
    assert( b() == 1 );

    assert( p && 1 );
    assert( 1 && p );
    assert( p || 0 );
    assert( 0 || p );
    assert( p && p );
    assert( p || p );

    while ( p )
        break;

    for ( ; p; )
        break;

    do break; while ( p );

    assert( p ? true : false );

    return 0;
}
