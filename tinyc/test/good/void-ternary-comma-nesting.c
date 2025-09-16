void foo() {}

int main()
{
    bool b = false;
    int x;
    x = ( b ? foo() : ( foo(), 20, b ? foo() : foo(), 12, foo() ),
            ( 12, b ? foo() : foo() ), foo(), 42 );
    assert( x == 42 );

    return 0;
}
