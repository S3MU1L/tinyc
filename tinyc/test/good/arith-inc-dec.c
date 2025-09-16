int main()
{
    int si = 0;
    int ui = 0;
    signed char sc = 0;
    unsigned char uc = 0;

    assert( si++ == 0 );
    assert( si-- == 1 );
    assert( ++si == 1 );
    assert( --si == 0 );

    assert( ui++ == 0 );
    assert( ui-- == 1 );
    assert( ++ui == 1 );
    assert( --ui == 0 );

    assert( sc++ == 0 );
    assert( sc-- == 1 );
    assert( ++sc == 1 );
    assert( --sc == 0 );

    assert( uc++ == 0 );
    assert( uc-- == 1 );
    assert( ++uc == 1 );
    assert( --uc == 0 );

    return 0;
}
