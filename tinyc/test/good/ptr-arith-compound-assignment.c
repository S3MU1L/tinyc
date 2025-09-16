int main()
{
    int *p = ( int * ) 100;

    p += 2;
    assert( ( int ) p == 100 + 2 * sizeof( int ) );
    assert( ( int ) ( p -= 3 ) == 100 - sizeof( int ) );
    assert( ( int ) p == 100 - sizeof( int ) );

    return 0;
}
