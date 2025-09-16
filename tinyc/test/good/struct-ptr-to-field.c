struct s
{
    int x;
    char a;
    char b;
};

int main()
{
    struct s s;
    s.x = 20;
    s.a = 100;
    s.b = 42;

    int *px = &s.x;
    char *pa = &s.a,
         *pb = &s.b;

    assert( *px == 20 );
    assert( *pa == 100 );
    assert( *pb == 42 );

    *px = 1;
    *pa = 2;
    *pb = 3;

    assert( s.x == 1 );
    assert( s.a == 2 );
    assert( s.b == 3 );

    return 0;
}
