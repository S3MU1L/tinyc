int main()
{
    char x[2] = { -1, -4 };
    char y = 0;
    assert ( x[0] >> 1u == -1 );
    x[1] >>= 1u;
    assert ( x[1] == -2 );
    return 0;
}
