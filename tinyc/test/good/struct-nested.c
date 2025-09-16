struct s1
{
    int x;
    int y;
};

struct s2
{
    int x;
    struct s1 s;
    int y;
};

struct s3
{
    int x;
    struct s2 s;
    int y;
};

int main()
{
    struct s3 s;

    s.x = 1;
    s.s.x = 2;
    s.s.s.x = 3;
    s.y = 4;
    s.s.y = 5;
    s.s.s.y = 6;

    assert( s.x == 1 );
    assert( s.s.x == 2 );
    assert( s.s.s.x == 3 );
    assert( s.y == 4 );
    assert( s.s.y == 5 );
    assert( s.s.s.y == 6 );

    return 0;
}
