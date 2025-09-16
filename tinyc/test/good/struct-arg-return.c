struct st { int x; };

struct st foo( struct st s, int x )
{
    if ( x > 0 )
    {
        assert( s.x == 0 );
        return foo( s, x - 1 );
    }

    s.x = 1;
    return s;
}

int main()
{
    struct st s;
    s.x = 0;

    assert( ( foo( s, 5 ) ).x == 1 );
    assert( s.x == 0 );
    assert( ( s = foo( s, 5 ) ).x == 1 );
    assert( s.x == 1 );

    return 0;
}
