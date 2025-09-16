int main()
{
    int x = 0,
        y = 0,
        z = 0;

    x = 1, y = 1 + x, z -= x += 3;

    assert( x == 4 );
    assert( y == 2 );
    assert( z == -4 );

    return 0;
}
