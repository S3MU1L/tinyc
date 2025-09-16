int main()
{
    int x = 1;
    assert ( x == 1 );

    x = 3;
    assert ( x == 3 );

    assert ( --x == 2 );
    assert ( x == 2 );
    assert ( ++x == 3 );
    assert ( x == 3 );

    assert( x++ == 3 );
    assert( x == 4 );
    assert( x-- == 4 );
    assert( x == 3 );

    x++;
    assert ( x == 4 );
    x--;
    assert ( x == 3 );

    &x;

    return 0;
}
