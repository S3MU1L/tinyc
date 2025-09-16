struct s
{
    int x;
    int y;
};

void cpy( void *dst, const void *src, int size )
{
    char *d = dst;
    const char *s = src;
    while ( size --> 0 )
    {
        *d++ = *s++;
    }
}

int main()
{
    struct s s1 = { 12, 13 },
             s2;

    cpy( &s2, &s1, sizeof ( struct s ) );

    assert( s2.x == 12 );
    assert( s2.y == 13 );

    return 0;
}
