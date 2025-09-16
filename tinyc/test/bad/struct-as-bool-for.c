struct s
{
    int x;
};

int main()
{
    struct s s;
    for ( ; s; )
        break;
    return 0;
}
