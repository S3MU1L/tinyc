struct s
{
    int x;
};
int main()
{
    bool b = true;
    struct s s;
    const struct s *cp = &s;

    ( b ? &s : cp )->x = 42;

    return 0;
}
