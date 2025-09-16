struct s
{
    int x;
};

struct s f()
{
    struct s s;
    s.x = 3;
    return s;
}

int main()
{
    int x = ( f().x = 5 );

    return 0;
}
