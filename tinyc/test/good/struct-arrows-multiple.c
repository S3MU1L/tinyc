struct s1
{
    char pad;
    int *p;
};

struct s2
{
    char pad;
    struct s1 *p;
    struct s1 s;
};

int main()
{
    struct s1 s1;
    int x;
    struct s2 s2,
              *p = &s2;

    s2.pad = 1;
    s2.p = &s1;
    s1.pad = 2;
    s1.p = &x;

    x = 42;
    assert( *p->p->p == 42 );
    *p->p->p = 66;
    assert( x == 66 );

    s2.s.pad = 3;
    assert( p->s.pad == 3 );
    p->s.pad = 4;
    assert( s2.s.pad == 4 );

    return 0;
}

