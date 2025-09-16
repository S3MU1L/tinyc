struct s
{
    int x,
        y;
};

int main()
{
    struct s s1;

    s1.x = 1;
    s1.y = 2;

    struct s s2 = ( 1, s1.y = 42, s1 );

    s1.x = 3;
    s1.y = 4;

    assert( s2.x == 1 );
    assert( s2.y == 42 );

    return 0;
}
