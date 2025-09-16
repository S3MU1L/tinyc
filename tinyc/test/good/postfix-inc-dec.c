int main()
{
    int x = 3;

    assert( x++ == 3 );
    assert( x == 4 );
    assert( x-- == 4 );
    assert( x == 3 );

    x++;
    assert ( x == 4 );
    x--;
    assert ( x == 3 );

    return 0;
}
