struct s
{
    int x,
        y;
};

struct s foo( struct s s )
{
    s.y *= 2;
    return s;
}

int main()
{
    struct s s1;

    s1.x = 1;
    s1.y = 2;

    struct s s2 = ( 1, s1.y = 21, foo( s1 ) );

    assert( s1.x == 1 );
    assert( s1.y == 21 );

    s1.x = 3;
    s1.y = 4;

    assert( s2.x == 1 );
    assert( s2.y == 42 );

    return 0;
}
