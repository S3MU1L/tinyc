int *func()
{
    static int arr[ 3 ];
    return arr;
}

int main()
{
    assert( func() == func() );
    func()[ 0 ] = 3;
    assert( func()[ 0 ] == 3 );

    return 0;
}
