int main()
{
    int x = 1;
    int l = -1;
    int r = -1;

    x = x ? ( l = 0 ) : ( r = 2 );

    assert( x == 0 );
    assert( l == 0 );
    assert( r == -1 );

    x = x ? ( l = 3 ) : ( r = 4 );

    assert( x == 4 );
    assert( l == 0 );
    assert( r == 4 );

    return 0;
}
