int fib( int n );

int main()
{
    assert( fib( 0 ) == 0 );

    int prev = 0;
    int n = 1;
    for ( int i = 1; i < 5; i += 1 )
    {
        assert( fib( i ) == n );

        int next = prev + n;
        prev = n;
        n = next;
    }

    return 0;
}

int fib( int n )
{
    if ( n <= 0 ) return 0;
    if ( n == 1 ) return 1;
    return fib( n - 1 ) + fib( n - 2 );
}
