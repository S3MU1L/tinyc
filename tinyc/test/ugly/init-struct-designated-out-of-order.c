struct s { int x, y; };
int main()
{
    struct s s = { .y = 1, .x = 0 };

    assert( s.x == 0 );
    assert( s.y == 1 );

    return 0;
}
