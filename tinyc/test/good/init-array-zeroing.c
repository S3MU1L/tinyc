int main()
{
    {
        // stain the stack
        int x[ 2 ];
        x[ 0 ] = 100;
        x[ 1 ] = 101;
    }

    int x[ 2 ] = { 1 };

    assert( x[ 0 ] == 1 );
    assert( x[ 1 ] == 0 );

    return 0;
}
