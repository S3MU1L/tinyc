int main()
{
    int x[ 2 ] = { [ 0 ] = 1, };

    assert( x[ 0 ] == 1 );
    assert( x[ 1 ] == 0 );

    return 0;
}
