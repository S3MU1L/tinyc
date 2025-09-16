int main()
{
    int x;
    int *p = &x,
        *q = &x;

    assert( p == q );
    return 0;
}
