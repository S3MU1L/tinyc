bool p2b( int *p ) { return p; }
bool b()
{
    int x[2];
    return x;
}

int main()
{
    int arr[ 2 ];

    assert( arr );
    assert( !arr == 0 );
    assert( !!arr );
    assert( !!arr == 1 );

    if ( arr )
        assert( true );
    if ( !arr )
        assert( false );

    if ( arr == 0 )
        assert( false );
    if ( arr != 0 )
        assert( true );

    assert( p2b( arr ) == 1 );
    assert( b() == 1 );

    assert( arr &&   1 );
    assert(   1 && arr );
    assert( arr ||   0 );
    assert(   0 || arr );
    assert( arr && arr );
    assert( arr || arr );

    while ( arr )
        break;

    for ( ; arr; )
        break;

    do break; while ( arr );

    assert( arr ? true : false );

    return 0;
}
