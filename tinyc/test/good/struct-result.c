struct s
{
    int x, y, z;
};

struct s f( int x, int y, int z )
{
    struct s s;
    s.x = x;
    s.y = y;
    s.z = z;
    return s;
}

int main()
{
    struct s x = f( 10, 20, 30 );
    assert( x.x == 10 );
    assert( x.y == 20 );
    assert( x.z == 30 );

    int y = ( x = f( 11, 21, 31 ) ).y;
    assert( y == 21 );
    assert( x.x == 11 );
    assert( x.y == 21 );
    assert( x.z == 31 );

    struct s z = ( x = f( 12, 22, 32 ) );
    assert( x.x == 12 );
    assert( x.y == 22 );
    assert( x.z == 32 );
    assert( z.x == 12 );
    assert( z.y == 22 );
    assert( z.z == 32 );

    return 0;
}
