struct s
{
    int x;
    char a;
    char b;
};

int main()
{
    struct s s,
             *p = &s;
    s.x = 20;
    s.a = 100;
    s.b = 42;

    assert( p->x == 20 );
    assert( p->a == 100 );
    assert( p->b == 42 );

    p->x = 1;
    p->a = 2;
    p->b = 3;

    assert( s.x == 1 );
    assert( s.a == 2 );
    assert( s.b == 3 );

    return 0;
}

