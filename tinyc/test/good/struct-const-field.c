struct s
{
    int x;
    const int y;
    int z;
};

int main()
{
    struct s s1 = { 12, 13, 14 };
    const struct s s2 = { 15, 16, 17 },
                   s3 = s1,
                   s4 = s2;

    assert( s1.x == 12 );
    assert( s1.y == 13 );
    assert( s1.z == 14 );

    assert( s2.x == 15 );
    assert( s2.y == 16 );
    assert( s2.z == 17 );

    assert( s3.x == 12 );
    assert( s3.y == 13 );
    assert( s3.z == 14 );

    assert( s4.x == 15 );
    assert( s4.y == 16 );
    assert( s4.z == 17 );

    return 0;
}
