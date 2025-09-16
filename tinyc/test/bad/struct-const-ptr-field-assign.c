struct s
{
    int x;
};

int main()
{
    struct s s;
    const struct s *p = &s;

    ( *p ).x = 4;

    return 0;
}
