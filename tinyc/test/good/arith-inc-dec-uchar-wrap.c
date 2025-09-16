int main()
{
    unsigned char uc = 0;

    assert( uc-- == 0 );
    assert( uc == 255 );
    assert( uc++ == 255 );
    assert( uc == 0 );

    --uc;
    assert( uc == 255 );
    ++uc;
    assert( uc == 0 );

    assert( --uc == 255 );
    assert( ++uc == 0 );

    return 0;
}
