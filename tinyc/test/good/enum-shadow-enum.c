enum {
    zero,
    one,
    ten = 10,
    eleven,
};

int main()
{
    assert( one );

    assert( zero == 0 );
    assert( one == 1 );
    assert( ten == 10 );
    assert( eleven == 11 );

    enum {
        zero = 3,
        ten,
    };

    assert( zero == 3 );
    assert( one == 1 );
    assert( ten == 4 );
    assert( eleven == 11 );

    return 0;
}
