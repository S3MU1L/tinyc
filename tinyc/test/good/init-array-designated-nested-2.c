struct s { int x, y; };

int main()
{
    struct s s[ 2 ] = { [ 0 ] = { 1 }, [ 1 ] = { .y = 4 } };

    assert( s[ 0 ].x == 1 );
    assert( s[ 0 ].y == 0 );
    assert( s[ 1 ].x == 0 );
    assert( s[ 1 ].y == 4 );

    return 0;
}
