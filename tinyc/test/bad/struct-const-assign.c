struct s
{
    int x;
};

int main()
{
    const struct s s;

    s.x = 4;

    return 0;
}
