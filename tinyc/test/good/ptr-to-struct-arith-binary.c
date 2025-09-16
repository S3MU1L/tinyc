struct p
{
    int x,
        y;
};

struct s
{
    struct p s1,
             s2;
};

int main()
{
    struct s s;
    struct p *p1 = &s.s1,
             *p2 = &s.s2;

    assert( p2 - p1 == 1 );
    assert( p2 - 1 == p1 );
    assert( 1 + p1 == p2 );

    return 0;
}
