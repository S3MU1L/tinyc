struct s { int x, y, z; };

struct s foo( struct s a, struct s b, struct s c, struct s d, struct s e,
              struct s f, struct s g )
{
    a.x = a.x + b.x + c.x + d.x + e.x + f.x + g.x;
    return a;
}

int main()
{
    int l1 = 1, l2 = 2, l3 = 3, l4 = 4, l5 = 5, l6 = 6, l7 = 7;

    struct s a, b, c, d, e, f, g;
    a.x = 10, a.y = 20;
    b.x = 11, b.y = 21;
    c.x = 12, c.y = 22;
    d.x = 13, d.y = 23;
    e.x = 14, e.y = 24;
    f.x = 15, f.y = 25;
    g.x = 16, g.y = 26;

    int x = foo( a, b, c, d, e, f, foo( a, b, c, d, e, f, g ) ).x;

    assert( x == 166 );

    return 0;
}
