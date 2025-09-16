struct s
{
    const int x;
};

int main()
{
    struct s a[ 1 ];
    a[ 0 ].x = 42;
    return 0;
}
