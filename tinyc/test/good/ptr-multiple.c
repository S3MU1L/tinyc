int main()
{
    int x = 42,
        *p = &x,
        **pp = &p,
        ***ppp = &pp,
        ****pppp = &ppp;

    assert( ****pppp == 42 );
    ****pppp = 20;

    assert( x == 20 );

    assert( ( ****pppp )++ == 20 );
    assert( x == 21 );
    assert( ++( ****pppp ) == 22 );
    assert( x == 22 );

    x = 1;
    ( ****pppp )++;
    assert( x == 2 );

    return 0;
}
