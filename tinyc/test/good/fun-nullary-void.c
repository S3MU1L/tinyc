int f( void ) { return 42; }
int g( void *p ) { return 2; }

int main()
{
    assert( f() == 42 );
    assert( g( 0 ) == 2 );
    return 0;
}
