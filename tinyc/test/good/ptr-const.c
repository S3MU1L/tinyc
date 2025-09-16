int main()
{
    int x = 42;
    const int *p = &x;

    assert( *p == 42 );

    return 0;
}
