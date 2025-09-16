struct s
{
    int x, y;
};

struct s ctor( int x )
{
    struct s s = { x, x * 10 };
    return s;
}

int main()
{
    struct s s = ctor( 1 );
    struct s arr[ 3 ] = { ctor( 2 ), ctor( 3 ), };

    assert( s.x == 1 );
    assert( s.y == 10 );
    assert( arr[ 0 ].x == 2 );
    assert( arr[ 0 ].y == 20 );
    assert( arr[ 1 ].x == 3 );
    assert( arr[ 1 ].y == 30 );
    assert( arr[ 2 ].x == 0 );
    assert( arr[ 2 ].y == 0 );

    return 0;
}
