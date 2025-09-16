struct s
{
    int x,
        y;
};
int main()
{
    {
        struct s s[ 3 ] = {
            { 100, 101 },
            { 102, 103 },
            { 104, 105 }
        };

        assert( s[ 0 ].x == 100 );
        assert( s[ 0 ].y == 101 );
        assert( s[ 1 ].x == 102 );
        assert( s[ 1 ].y == 103 );
        assert( s[ 2 ].x == 104 );
        assert( s[ 2 ].y == 105 );
    }
    struct s s[ 3 ] = { { 1, }, { 3, 4 },  };

    assert( s[ 0 ].x == 1 );
    assert( s[ 0 ].y == 0 );
    assert( s[ 1 ].x == 3 );
    assert( s[ 1 ].y == 4 );
    assert( s[ 2 ].x == 0 );
    assert( s[ 2 ].y == 0 );

    return 0;
}
