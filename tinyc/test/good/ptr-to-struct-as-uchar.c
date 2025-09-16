struct p
{
    int x,
        y;
};

struct s
{
    struct p s1,
             s2;
};

int main()
{
    struct s s;
    unsigned char *p1 = ( unsigned char * ) &s.s1,
                  *p2 = ( unsigned char * ) &s.s2;

    assert( p2 - p1 == 2 * sizeof( int ) );
    assert( p2 - 2 * sizeof( int ) == p1 );
    assert( 2 * sizeof( int ) + p1 == p2 );

    return 0;
}
