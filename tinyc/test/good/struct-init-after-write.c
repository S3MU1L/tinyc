struct s { int x; char y; };

struct s evil( struct s *p )
{
    struct s res = { 42, 12 };
    *p = res;
    res.y = 20;
    return res;
}

int main()
{
    struct s s = evil( &s );

    assert( s.x == 42 );
    assert( s.y == 20 );

    return 0;
}
