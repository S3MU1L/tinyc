struct s
{
    int x;
    int y;
    int z;
};

int f( struct s s, int y )
{
    assert( s.y == y );

    int r = 100 * s.x + 10 * s.y + s.z;

    s.x = 200;
    s.y = 100;
    s.z = 50;

    assert( s.x == 200 );
    assert( s.y == 100 );
    assert( s.z == 50 );

    return r;
}

int main()
{
    struct s s;
    s.x = 7;
    s.y = 5;
    s.z = 3;

    assert( f( s, 5 ) == 753 );
    assert( s.x == 7 );
    assert( s.y == 5 );
    assert( s.z == 3 );

    return 0;
}

