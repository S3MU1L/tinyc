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

int f( struct s2 s, int x )
{
    assert( s.s.x == x );
    int r = 100 * s.s.x;
    s.s.x = 200;
    s.x = 1;
    s.y = 2;
    assert( s.s.x == 200 );
    return r;
}

int main()
{
    struct s2 s;
    s.x = 7;
    s.y = 5;
    s.s.x = 10;

    assert( f( s, 10 ) == 1000 );

    assert( s.x == 7 );
    assert( s.s.x == 10 );
    assert( s.y == 5 );

    return 0;
}

