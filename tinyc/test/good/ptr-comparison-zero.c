int main()
{
    int x;
    int  *ip = &x;
    void *vp = &x;
    const int  *cip = &x;
    const void *cvp = &x;

    assert( ip  != 0 );
    assert( vp  != 0 );
    assert( cip != 0 );
    assert( cvp != 0 );

    assert( 0 != ip  );
    assert( 0 != vp  );
    assert( 0 != cip );
    assert( 0 != cvp );

    assert( !( ip  == 0 ) );
    assert( !( vp  == 0 ) );
    assert( !( cip == 0 ) );
    assert( !( cvp == 0 ) );

    assert( !( 0 == ip  ) );
    assert( !( 0 == vp  ) );
    assert( !( 0 == cip ) );
    assert( !( 0 == cvp ) );


    return 0;
}
