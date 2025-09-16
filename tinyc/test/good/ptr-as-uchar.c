struct s
{
    int x,
        y;
};

int main()
{
    struct s s;
    unsigned char *px = ( unsigned char * ) &s.x,
                  *py = ( unsigned char * ) &s.y;

    assert( py - px == sizeof( int ) );
    assert( py - sizeof( int ) == px );
    assert( sizeof( int ) + px == py );

    return 0;
}
