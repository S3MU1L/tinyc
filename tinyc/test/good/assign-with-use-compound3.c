int main()
{
    unsigned x = 10;
    x *= 1 + x;
    assert( x == 110 );
    return 0;
}
