int main()
{
    int x = 0;

    x && ( x = 1 );
    assert( x == 0 );

    x || ( x = 2 );
    assert( x == 2 );

    x || ( x = 3 );
    assert( x == 2 );

    x && ( x = 4 );
    assert( x == 4 );

    return 0;
}
