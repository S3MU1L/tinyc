int main()
{
    unsigned char uc = 0;

    assert( ( uc -= 1 ) == 255 );
    assert( uc == 255 );

    assert( ( uc += 1 ) == 0 );
    assert( uc == 0 );

    return 0;
}
