int main()
{
    unsigned x = 21;
    x *= 1;
    x &= 0xffffu;
    x += 0;
    assert( x == 21 );
    return 0;
}
