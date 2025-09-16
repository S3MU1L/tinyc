int main()
{
    int x = 42;
    void *p = &x;

    * (int *) p = 20;

    assert( x == 20 );

    return 0;
}
