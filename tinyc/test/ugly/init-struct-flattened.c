struct s1
{
    int x,
        y;
};
struct s2
{
    int w;
    struct s1 x,
              y;
    int z;
};
int main()
{
    struct s2 s = { 1, 2, 3, 4, 5, 6 };
    return 0;
}
