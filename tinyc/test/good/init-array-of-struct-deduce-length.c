struct s
{
    int x[3];
};
int main()
{
    struct s a[] = { {{ 1, 2 }}, {{ 3, }} };

    assert( a[ 0 ].x[ 0 ] == 1 );
    assert( a[ 0 ].x[ 1 ] == 2 );
    assert( a[ 0 ].x[ 2 ] == 0 );
    assert( a[ 1 ].x[ 0 ] == 3 );
    assert( a[ 1 ].x[ 1 ] == 0 );

    return 0;
}
