int main()
{
    int x[] = { 42, x[ 0 ] + 24 };

    assert( x[ 0 ] == 42 );
    assert( x[ 1 ] == 66 );

    return 0;
}
