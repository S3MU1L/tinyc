int main()
{
    int x = 42;
    assert( x == 42 );

    int *p = &x;
    *p = 66;

    assert( x == 66 );

    return 0;
}
