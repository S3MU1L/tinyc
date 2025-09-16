struct s1
{
    int x;
};
struct s2
{
    struct s1 s[ 2 ];
};

int main()
{
    const struct s2 s[ 1 ];
    s[ 0 ].s[ 1 ].x = 42;
    return 0;
}
