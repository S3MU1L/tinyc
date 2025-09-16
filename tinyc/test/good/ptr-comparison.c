int main()
{
    int x = 20;
    int *p = &x;
    const int *cp = &x;

    assert( p == cp );
    assert( *p == *cp );
    assert( *p <= *cp );
    assert( *p >= *cp );

    return 0;
}
