struct s
{
    int x;
};

int main()
{
    struct s s = { 1 },
             t = { 1 };
    s == t;
    return 0;
}
