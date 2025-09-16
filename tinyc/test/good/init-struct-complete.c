struct s
{
    int x,
        y;
};
int main()
{
    struct s s = { 1, 2 };

    assert( s.x == 1 );
    assert( s.y == 2 );

    return 0;
}
