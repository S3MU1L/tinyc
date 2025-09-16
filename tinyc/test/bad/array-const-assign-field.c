struct s
{
    int x;
};

int main()
{
    const struct s a[ 1 ];
    a[ 0 ].x = 42;
    return 0;
}
