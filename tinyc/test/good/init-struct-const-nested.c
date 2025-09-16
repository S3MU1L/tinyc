struct s1
{
    const int x;
};

struct s2
{
    const struct s1 s;
};

struct s3
{
    const struct s2 s;
};

int main()
{
    const struct s3 s = {{{ 42 }}};
    assert( s.s.s.x == 42 );
    return 0;
}
