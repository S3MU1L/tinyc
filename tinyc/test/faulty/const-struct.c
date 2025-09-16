struct s { int x; char y; };

struct s evil( struct s *p )
{
    struct s res = { 42, 12 };
    *p = res;
    return res;
}

int main()
{
    const struct s cs = evil( ( struct s * ) &cs );

    return 0;
}
