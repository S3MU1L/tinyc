int gib( int x ) { return x; }
int main()
{
    int x;
    bool b = true;
    x = b ? ( x = gib( 42 ) ) : gib( 66 );

    assert( x == 42 );
    return 0;
}
