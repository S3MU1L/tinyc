struct s
{
    int x,
        y;
};
int main()
{
    {
        // stain the stack
        struct s s;
        s.x = 100;
        s.y = 101;
    }

    struct s s = { 1 };

    assert( s.x == 1 );
    assert( s.y == 0 );

    return 0;
}
