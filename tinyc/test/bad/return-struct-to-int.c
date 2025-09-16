struct st { int x; };

int foo( int x )
{
    struct st s;
    s.x = x;
    return s;
}

int main()
{
    foo( 2 );
    return 0;
}
