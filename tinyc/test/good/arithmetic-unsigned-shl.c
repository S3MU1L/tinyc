int main()
{
    unsigned x = 0x4000u;
    x <<= 1;
    assert( x == 0x8000u );
    return 0;
}
