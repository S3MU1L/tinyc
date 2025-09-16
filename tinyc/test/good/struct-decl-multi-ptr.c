struct s
{
    int *p,
        *q;
};

int main()
{
    struct s s;
    s.p - s.q;
    s.p == s.q;
    s.p = s.q;

    return 0;
}
