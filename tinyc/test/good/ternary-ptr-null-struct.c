struct s
{
    int x;
};
int main()
{
    bool b = true;
    struct s s;

    ( b ? &s : NULL )->x = 42;
    assert( s.x == 42 );

    return 0;
}
