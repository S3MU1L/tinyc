struct s
{
    int x,
        y;
};

int main()
{
    struct s s1;
    s1.x = 42;
    s1.y = 66;

    struct s s2,
             s3;

    s3 = s2 = s1;

    s1.x = 1;
    s1.y = 2;

    assert( s2.x == 42 );
    assert( s2.y == 66 );
    assert( s3.x == 42 );
    assert( s3.y == 66 );

    return 0;
}
