struct s1
{
    int x;
};
struct s2
{
    int x;
    struct s1 s;
    int y;
};

int f( struct s1 s, int x )
{
    assert( s.x == x );
    int r = 100 * s.x;
    s.x = 200;
    assert( s.x == 200 );
    return r;
}

int main()
{
    struct s2 s;
    s.x = 7;
    s.y = 5;
    s.s.x = 10;

    assert( f( s.s, 10 ) == 1000 );

    assert( s.x == 7 );
    assert( s.s.x == 10 );
    assert( s.y == 5 );

    return 0;
}

