int main()
{
    unsigned x = 0x7fff;
    x *= x;
    x &= 0xffffu;
    assert( x == 1 );
    return 0;
}
