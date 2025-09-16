struct s1
{
    int x,
        y;
};
struct s2
{
    int w;
    struct s1 x,
              y;
    int z;
};
int main()
{
    struct s2 s = { 1, { 2, 3 }, { 4, 5 }, 6 };

    assert( s.w == 1 );
    assert( s.x.x == 2 );
    assert( s.x.y == 3 );
    assert( s.y.x == 4 );
    assert( s.y.y == 5 );
    assert( s.z == 6 );

    return 0;
}
