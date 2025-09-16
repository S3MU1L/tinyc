struct s1 { int x, y; };
struct s2 { struct s1 a, b; };

int main()
{
    struct s2 s = { .a = { .x = 1, .y = 2 }, .b = { 3, 4 } };

    assert( s.a.x == 1 );
    assert( s.a.y == 2 );
    assert( s.b.x == 3 );
    assert( s.b.y == 4 );

    return 0;
}
