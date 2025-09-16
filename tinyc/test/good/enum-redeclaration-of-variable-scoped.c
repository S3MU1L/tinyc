int main()
{
    int x = 10;

    assert( x == 10 );

    {
        enum {
            x = 20,
        };

        assert( x == 20 );
    }

    assert( x == 10 );

    return 0;
}
