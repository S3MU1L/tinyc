int main()
{
    int arr[ 10 ],
        *p = arr;
    const int *q = p;

    for ( int i = 0; i < 10; ++i )
    {
        *p++ = i;
    }
    for ( int i = 0; i < 10; ++i )
    {
        assert( *q++ == i );
        assert( arr[ i ] == i );
    }

    assert( p == q );
    assert( q - arr == 10 );

    return 0;
}
