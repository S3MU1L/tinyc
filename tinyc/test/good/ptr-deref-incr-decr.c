int main()
{
    int x = 42,
        *p = &x;

    assert( ( *p )++ == 42 );
    assert( x == 43 );
    assert( ++( *p ) == 44 );
    assert( x == 44 );

    ( *p )++;
    assert( x == 45 );
    ++( *p );
    assert( x == 46 );

    assert( ( *p )-- == 46 );
    assert( x == 45 );
    assert( --( *p ) == 44 );
    assert( x == 44 );

    ( *p )--;
    assert( x == 43 );
    --( *p );
    assert( x == 42 );

    return 0;
}
