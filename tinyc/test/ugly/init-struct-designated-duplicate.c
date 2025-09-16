struct s { int x, y; };
int main()
{
    struct s s = { .x = 1, .x = 2 };

    assert( s.x == 2 );
    assert( s.y == 0 );

    return 0;
}
