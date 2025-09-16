int main()
{
    int x = 42;
    assert( x == 42 );

    *&x = 66;

    assert( x == 66 );

    *&*&*&x = 100;

    assert( x == 100 );

    return 0;
}
