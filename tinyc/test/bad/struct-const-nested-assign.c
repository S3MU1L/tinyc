struct s1
{
    int x;
};

struct s2
{
    struct s1 s;
};

struct s3
{
    const struct s2 s;
};

int main()
{
    struct s3 s;
    s.s.s.x = 42;
    return 0;
}
