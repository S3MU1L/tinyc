struct s1
{
    int x;
};
struct s2
{
    const struct s1 s[ 2 ];
};

int main()
{
    struct s2 s;
    s.s[ 1 ].x = 42;
    return 0;
}
