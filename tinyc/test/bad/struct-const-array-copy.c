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
    struct s2 s, t;
    s = t;
    return 0;
}
