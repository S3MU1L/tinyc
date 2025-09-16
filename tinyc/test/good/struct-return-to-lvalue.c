struct sub { int x; };

struct super
{
    int x;
    struct sub *ptr;
    struct sub subs[ 2 ];
    int y;
};

struct sub getsub( int x )
{
    struct sub s = { x };
    return s;
}

int main()
{
    struct sub subs[ 2 ] = { { 0 }, },
               *ptr = subs;
    struct super s = { 2, subs };

    *s.subs      = getsub( 10 );
     s.subs[ 1 ] = getsub( 11 );
    *s.ptr       = getsub( 12 );
     s.ptr[ 1 ]  = getsub( 13 );

     assert( s.x == 2 );
     assert( s.subs[ 0 ].x == 10 );
     assert( s.subs[ 1 ].x == 11 );
     assert( subs[ 0 ].x == 12 );
     assert( subs[ 1 ].x == 13 );
     assert( s.y == 0 );

     *ptr = getsub( 14 );
     ptr[ 1 ] = getsub( 15 );

     assert( subs[ 0 ].x == 14 );
     assert( subs[ 1 ].x == 15 );

     *subs = getsub( 16 );
     subs[ 1 ] = getsub( 17 );

     assert( subs[ 0 ].x == 16 );
     assert( subs[ 1 ].x == 17 );

    return 0;
}
