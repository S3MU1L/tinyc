struct st { int x; int y; };

struct st foo( int x )
{
    struct st s;
    s.x = x;
    s.y = x;
    return s;
}

struct st bar( int x )
{
    return foo( x * 2 );
}

int main()
{
    assert( foo( 3 ).y == 3 );
    struct st s;
    assert( ( s = foo( 4 ) ).y == 4 );
    assert( s.x == 4 );

    assert( bar( 5 ).x == 10 );

    return 0;
}
