struct s
{
    int x;
};
int main()
{
    bool b = true;
    struct s s;
    void *vp = &s;

    ( b ? &s : vp )->x = 42;

    return 0;
}
