struct s { int x, y; };
int main()
{
    struct s s = { .x = 1, .y = 2 };

    assert( s.x == 1 );
    assert( s.y == 2 );

    return 0;
}
