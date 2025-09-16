int foo()
{
    return 42;
    return 66;
}

int main()
{
    assert( foo() == 42 );
    return 0;
}
