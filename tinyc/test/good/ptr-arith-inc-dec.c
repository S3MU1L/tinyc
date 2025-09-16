int main()
{
    int *p = ( int * ) 100;

    assert( ( int ) p++ == 100 );
    assert( ( int ) p   == 100 + sizeof( int ) );
    assert( ( int ) ++p == 100 + 2 * sizeof( int ) );

    assert( ( int ) p-- == 100 + 2 * sizeof( int ) );
    assert( ( int ) p   == 100 + sizeof( int ) );
    assert( ( int ) --p == 100 );

    return 0;
}
