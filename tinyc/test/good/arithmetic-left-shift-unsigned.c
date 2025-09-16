int main()
{
    int y = 1;
    int x = -1u << y;
    assert( x == -2 );
    return 0;
}
