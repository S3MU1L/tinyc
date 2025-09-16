void foo() {}

int main()
{
    42, foo();
    foo(), foo();
    foo(), 42, foo();
    int x = ( foo(), 42 );
    assert( x == 42 );

    return 0;
}
