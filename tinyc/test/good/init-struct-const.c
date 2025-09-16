struct s
{
    const int x;
};
int main()
{
    struct s s = { 1 };
    const struct s t = { 2 };

    assert( s.x == 1 );
    assert( t.x == 2 );

    return 0;
}
