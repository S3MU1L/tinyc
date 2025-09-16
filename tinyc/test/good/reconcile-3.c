int foo( unsigned x ) { return x; }
int bar( unsigned n )
{
    foo( 7 );
    int lol; // this shouldn't steal n's register
    return n == 0 // this shouldn't link n to rv
        || foo( 0 );
}

int main()
{
    assert( bar( 0 ) == 1 );
    assert( bar( 8 ) == 0 );
    return 0;
}
