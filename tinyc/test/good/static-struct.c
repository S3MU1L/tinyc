struct foo
{
    int x;
    int y;
};

struct foo *func()
{
    static struct foo foo;
    return &foo;
}

int main()
{
    assert( func() == func() );
    func()->x = 3;
    assert( func()->x == 3 );

    return 0;
}
