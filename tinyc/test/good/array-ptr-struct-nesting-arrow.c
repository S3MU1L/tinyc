struct pair
{
    int x;
    int y;
};
struct arr
{
    int pad1;
    struct pair data[4];
    int pad2;
};

int main()
{
    assert( sizeof( struct pair ) == 2 * sizeof( int ) );
    assert( sizeof( struct arr ) == 10 * sizeof( int ) );

    struct arr _data[ 2 ],
               *data = _data;

    ( data + 1 )->data[ 3 ].y = 4;
    assert( ( data + 1 )->data[ 3 ].y == 4 );

    int *p = ( int * ) data;
    p += 18;
    assert( *p == 4 );

    int one = 1,
        zero = 0;

    ( data + 1 )->data[ one ].y = 6;
    assert( ( data + 1 )->data[ one ].y == 6 );

    assert( *p == 4 );
    p -= 4;
    assert( *p == 6 );

    ( data + one )->data[ one ].y = 5;
    assert( ( data + one )->data[ one ].y == 5 );
    assert( *p == 5 );

    ( data + one + zero )->data[ one ].y = 7;
    assert( ( data + one + zero )->data[ one ].y == 7 );
    assert( *p == 7 );

    ( data + 1 )->data[ one + one ].y = 8;
    assert( ( data + 1 )->data[ one + one ].y == 8 );

    assert( *p == 7 );
    p += 2;
    assert( *p == 8 );

    ( data + one )->data[ one + one ].y = 10;
    assert( ( data + one )->data[ one + one ].y == 10 );
    assert( *p == 10 );

    ( data + one + zero )->data[ one + one ].y = 12;
    assert( ( data + one + zero )->data[ one + one ].y == 12 );
    assert( *p == 12 );

    ( data + one + zero )->data[ 2 ].y = 15;
    assert( ( data + one + zero )->data[ 2 ].y == 15 );
    assert( *p == 15 );

    ( data + one )->data[ 2 ].y = 17;
    assert( ( data + one )->data[ 2 ].y == 17 );
    assert( *p == 17 );

    return 0;
}
