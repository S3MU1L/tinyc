unsigned foo(unsigned a, unsigned b) { return a + b; }
unsigned bar( unsigned a1, unsigned a2, unsigned a3 )
{
    unsigned x = foo( a1, a3 );
    unsigned y = foo( a2, a3 );
    unsigned z = 0;

    for ( unsigned i = 0; i < x; ++i )
    {
        if ( a1 % a3 != a2 % a3 )
            z++;

        a1 += a3;
        a2 -= a3;
    }

    return 0;
}
int main()
{
    return 0;
}
