struct s
{
    int x;
    const int y;
    int z;
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
    struct s s1 = { 12, 13, 14 },
             s2[ 2 ];

    cpy( s2 + 1, &s1, sizeof ( struct s ) );

    return 0;
}
