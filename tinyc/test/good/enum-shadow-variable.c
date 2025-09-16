enum {
    x = 10,
};

int main()
{
    assert( x == 10 );

    {
        int x = 12;
        assert( x == 12 );
        x = 3;
        assert( x == 3 );
    }

    assert( x == 10 );

    return 0;
}
