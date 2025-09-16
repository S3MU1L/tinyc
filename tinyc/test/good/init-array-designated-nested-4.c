struct s { int x, y; };

int main()
{
    struct s s[ 2 ] = { { .y = 2, }, { 3, }, };

    assert( s[ 0 ].x == 0 );
    assert( s[ 0 ].y == 2 );
    assert( s[ 1 ].x == 3 );
    assert( s[ 1 ].y == 0 );

    return 0;
}
