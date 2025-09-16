int ix( int *arr, int i )
{
    return arr[ i ];
}

int main()
{
    int arr[ 10 ];
    arr[ 5 ] = 42;

    assert( ix( arr, 5 ) == 42 );

    return 0;
}
