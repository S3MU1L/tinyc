struct s
{
    int x;
    int y;
};

int main()
{
    struct s s1,
             s2,
             *p1 = &s1,
             *p2 = &s2;

    s1.x = 10;
    s1.y = 20;

    *p2 = s1;

    assert( s2.x == 10 );
    assert( s2.y == 20 );

    s2.x = 1;
    s2.y = 2;

    s1 = *p2;

    assert( s1.x == 1 );
    assert( s1.y == 2 );

    s1.x = 5;
    s1.y = 6;

    *p2 = *p1;

    assert( s2.x == 5 );
    assert( s2.y == 6 );

    return 0;
}
