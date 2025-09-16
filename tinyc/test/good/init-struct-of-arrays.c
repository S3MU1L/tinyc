struct s
{
    int x[ 2 ],
        y[ 2 ],
        z[ 2 ];
};
int main()
{
    {
        struct s s = {
            { 100, 101 },
            { 102, 103 },
            { 104, 105 }
        };

        assert( s.x[ 0 ] == 100 );
        assert( s.x[ 1 ] == 101 );
        assert( s.y[ 0 ] == 102 );
        assert( s.y[ 1 ] == 103 );
        assert( s.z[ 0 ] == 104 );
        assert( s.z[ 1 ] == 105 );
    }
    struct s s = { { 1, }, { 3, 4 },  };

    assert( s.x[ 0 ] == 1 );
    assert( s.x[ 1 ] == 0 );
    assert( s.y[ 0 ] == 3 );
    assert( s.y[ 1 ] == 4 );
    assert( s.z[ 0 ] == 0 );
    assert( s.z[ 1 ] == 0 );

    return 0;
}
