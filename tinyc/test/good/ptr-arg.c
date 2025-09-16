int f( int *p )
{
    int x = *p + 2;
    *p -= 2;
    return x;
}

int main()
{
    int x = 42;

    assert( f( &x ) == 44 );
    assert( x == 40 );

    return 0;
}
