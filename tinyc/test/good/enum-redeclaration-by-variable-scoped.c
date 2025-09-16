int main()
{
    enum {
        x = 10,
    };

    assert( x == 10 );

    {
        int x = 20;
        assert( x == 20 );
    }

    assert( x == 10 );

    return 0;
}
