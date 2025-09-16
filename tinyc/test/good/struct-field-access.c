struct s
{
    int x;
    char a;
    char b;
};

int main()
{
    struct s s;
    s.x = 20;
    s.a = 100;
    s.b = 42;

    assert( s.x == 20 );
    assert( s.a == 100 );
    assert( s.b == 42 );

    return 0;
}
