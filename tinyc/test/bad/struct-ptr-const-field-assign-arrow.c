struct s
{
    const int x;
};

int main()
{
    struct s s;
    struct s *p = &s;

    p->x = 4;

    return 0;
}

