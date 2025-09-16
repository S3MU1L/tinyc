int main()
{
    unsigned char uc = 0;
    int x = 0x6642;

    assert( ( uc = x ) == 0x42 );
    assert( uc == 0x42 );
    assert( x == 0x6642 );

    return 0;
}
