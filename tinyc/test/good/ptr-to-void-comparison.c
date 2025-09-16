struct s
{
    int x,
        y;
};

int main()
{
    struct s s;
    void *px = &s.x,
         *py = &s.y;

    assert( px == px );
    assert( px != py );
    assert( px < py );
    assert( py > px );

    return 0;
}

