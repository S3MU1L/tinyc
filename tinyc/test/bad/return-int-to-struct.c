struct st { int x; };

struct st foo( int x )
{
    return x;
}

int main()
{
    foo( 2 );
    return 0;
}
