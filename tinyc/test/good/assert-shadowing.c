struct assert
{
    int assert;
    struct assert *x;
};

int foo( int assert )
{
    return assert;
}

int main()
{
    struct assert a;
    a.assert = 5;

    assert( foo( 1 ) );

    int assert = 2;
    // OK in C, but pointless to emulate:
    // assert( assert );

    return 0;
}
