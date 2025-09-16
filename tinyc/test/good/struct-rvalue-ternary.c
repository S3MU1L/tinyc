struct s
{
    int x,
        y;
};

int main()
{
    struct s s1,
             s2;

    s1.x = 1;
    s1.y = 2;
    s2.x = -1;
    s2.y = -2;

    struct s s3 = ( s1.x > 0 ) ? s1 : s2;

    s1.x = 3;
    s1.y = 4;
    s2.x = -3;
    s2.y = -4;

    assert( s3.x == 1 );
    assert( s3.y == 2 );

    s3 = ( s2.x > 0 ) ? s1 : s2;

    s1.x = 5;
    s1.y = 6;
    s2.x = -5;
    s2.y = -6;

    assert( s3.x == -3 );
    assert( s3.y == -4 );

    return 0;
}
