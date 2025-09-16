struct s
{
    int x;
};

int main()
{
    struct s s1,
             s2;

    ( s1.x ? s1 : s2 ).x = 42;

    return 0;
}
