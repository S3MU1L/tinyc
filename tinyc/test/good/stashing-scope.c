int main()
{
    int a = 1;
    {
        assert( a == 1 );

        int b = 2;
        a = 3;
        assert( a == 3 );

        &a, &b;
    }
    {
        int a = 5;
    }
    assert( a == 3 );

    int b = 7;
    assert( a == 3 );

    return 0;
}
