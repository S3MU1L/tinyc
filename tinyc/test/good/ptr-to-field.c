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

    struct s *ps = &s;

    assert( ( *ps ).x == 20 );
    assert( ( *ps ).a == 100 );
    assert( ( *ps ).b == 42 );

    int *px = &( *ps ).x;
    char *pa = &( *ps ).a,
         *pb = &( *ps ).b;

    assert( *px == 20 );
    assert( *pa == 100 );
    assert( *pb == 42 );

    *px = 1;
    *pa = 2;
    *pb = 3;

    assert( ( *ps ).x == 1 );
    assert( ( *ps ).a == 2 );
    assert( ( *ps ).b == 3 );

    assert( s.x == 1 );
    assert( s.a == 2 );
    assert( s.b == 3 );

    ( *ps ).x = 5;
    ( *ps ).a = ( *ps ).b;
    ( *ps ).b = 6;

    assert( s.x == 5 );
    assert( s.a == 3 );
    assert( s.b == 6 );

    return 0;
}
