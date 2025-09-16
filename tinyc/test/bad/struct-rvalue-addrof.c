struct s
{
    int x;
};

int main()
{
    struct s s;
    &( 1, s );
    return 0;
}
