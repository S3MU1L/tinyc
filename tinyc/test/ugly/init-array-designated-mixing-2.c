int main()
{
    int x[ 2 ] = { [ 0 ] = 1, 2 };

    assert( x[ 0 ] == 1 );
    assert( x[ 1 ] == 2 );

    return 0;
}
