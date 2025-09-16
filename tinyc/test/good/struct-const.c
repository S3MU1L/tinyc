struct s { int x; char y; };

const struct s foo( const struct s x )
{
    const struct s y = x;
    return y;
}

struct s bar( struct s x )
{
    struct s y = x;
    return y;
}

const struct s baz( struct s *p )
{
    return *p;
}

int main()
{
    struct s s = { 4, 5 };
    const struct s cs = { 10, 20 };

    s = foo( s );

    const struct s r1 = foo( s ),
                   r2 = foo( cs ),
                   r3 = bar( s ),
                   r4 = bar( cs ),
                   r5 = baz( ( struct s * ) &cs );

    assert( s.x == 4 );
    assert( s.y == 5 );
    assert( cs.x == 10 );
    assert( cs.y == 20 );

    assert( r1.x == 4 );
    assert( r1.y == 5 );
    assert( r2.x == 10 );
    assert( r2.y == 20 );
    assert( r3.x == 4 );
    assert( r3.y == 5 );
    assert( r4.x == 10 );
    assert( r4.y == 20 );
    assert( r5.x == 10 );
    assert( r5.y == 20 );

    return 0;
}
