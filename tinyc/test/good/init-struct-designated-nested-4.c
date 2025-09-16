struct s1 { int x, y; };
struct s2 { struct s1 a, b; };

int main()
{
    struct s2 s = { .b = { .y = 4 } };

    assert( s.a.x == 0 );
    assert( s.a.y == 0 );
    assert( s.b.x == 0 );
    assert( s.b.y == 4 );

    return 0;
}
