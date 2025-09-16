int foo( int x );

int main()
{
    assert( foo( 1 ) == 42 );
    return 0;
}

int foo( int x ) { return x + 41; }
