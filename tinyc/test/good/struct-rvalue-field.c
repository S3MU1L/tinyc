struct s
{
    int x,
        y;
};

int main()
{
    struct s s1,
             s2;

    s1.x = 42;
    s1.y = 2;

    int x = ( s2 = s1 ).x;

    assert( s2.x == 42 );
    assert( x == 42 );

    s2.y = -2;

    assert( ( s2 = s1 ).y == 2 );

    return 0;
}
