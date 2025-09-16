struct s1 { int x, y; };
struct s2 { struct s1 a, b; };

int main()
{
    struct s2 s = { .b.x = 3 };

    assert( s.a.x == 0 );
    assert( s.a.y == 0 );
    assert( s.b.x == 3 );
    assert( s.b.y == 0 );

    return 0;
}
