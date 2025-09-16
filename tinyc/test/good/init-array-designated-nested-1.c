struct s { int x, y; };

int main()
{
    struct s s[ 2 ] = { [ 0 ] = { 1, 2 }, [ 1 ] = { 3, 4 } };

    assert( s[ 0 ].x == 1 );
    assert( s[ 0 ].y == 2 );
    assert( s[ 1 ].x == 3 );
    assert( s[ 1 ].y == 4 );

    return 0;
}
