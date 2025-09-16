int main()
{
    int *p = NULL;
    assert( 0 == p );

    p = 0;
    assert( p == NULL );

    assert( !NULL );
    assert( NULL == 0 );

    const int *cp = NULL;
    const void *cvp = NULL;
    void *vp = NULL;

    assert( cp == NULL );
    assert( cvp == NULL );
    assert( vp == NULL );

    assert( !&*p );
    assert( !&*cp );

    return 0;
}
