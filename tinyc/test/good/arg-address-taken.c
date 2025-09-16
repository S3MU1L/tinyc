int foo( int x )
{
    int *p = &x;
    *p += 1;
    return x;
}
int main()
{
    assert( foo( 42 ) == 43 );
    return 0;
}
