struct s1
{
    const int x;
};
struct s2
{
    struct s1 s[ 2 ];
};

int main()
{
    const struct s2 s[ 1 ] = {{{{ 42 }}}};
    assert( s[ 0 ].s[ 0 ].x == 42 );
    assert( s[ 0 ].s[ 1 ].x == 0 );
    return 0;
}
