int main()
{
    int x[ 2 ] = { [ 1 ] = 2, };

    assert( x[ 0 ] == 0 );
    assert( x[ 1 ] == 2 );

    return 0;
}
