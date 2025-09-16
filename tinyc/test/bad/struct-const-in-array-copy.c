struct s1
{
    const int x;
};
struct s2
{
    struct s1 s[ 2 ];
};

int main()
{
    struct s2 s, t;
    s = t;
    return 0;
}
