struct s
{
    int x,
        y;
};

int main()
{
    struct s s;
    int *px = &s.x,
        *py = &s.y;

    assert( px == px );
    assert( px != py );
    assert( px < py );
    assert( py > px );

    assert( px - py == -1 );
    assert( py - px == 1 );
    assert( px + 1 == py );
    assert( 1 + px == py );
    assert( py - 1 == px );

    return 0;
}
