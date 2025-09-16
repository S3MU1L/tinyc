int main()
{
    int x = 42;
    assert( x == 42 );

    int *p = &x;
    assert( *p == 42 );

    x = 66;
    assert( *p == 66 );

    return 0;
}
