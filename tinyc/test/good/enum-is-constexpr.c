enum {
    size = 10,
};

int main()
{
    int arr[ size ];
    arr[ 9 ] = 5;
    assert( arr[ 9 ] == 5 );

    return 0;
}
