int main()
{
    const int ca[1];
    const int *cp = ca;

    assert( ca == cp );

    int a[1];
    int *p = a;
    cp = a;

    assert( cp == p );

    return 0;
}
