unsigned foo( unsigned x, unsigned y )
{
    const unsigned a = 0;
    unsigned b = 0, c = 0, d = 0;

    unsigned e = 4;
    unsigned f = 0;

    assert( f == 0 );
    f = e;
    e = 7;
    assert( f == 4 );
    assert( e == 7 );

    return 0;
}

int main()
{
    return foo( 0, 0 );
}
