struct s
{
    int x;
};

int unwrap( struct s s )
{
    return s.x;
}

int main()
{
    struct s s1,
             s2;

    s1.x = 42;
    s2.x = 65;

    assert( unwrap( s1.x ? s1 : s2 ) == 42 );
    assert( unwrap( ( ++s2.x, s1 = s2, ++s2.x, s1 ) ) == 66 );

    return 0;
}
