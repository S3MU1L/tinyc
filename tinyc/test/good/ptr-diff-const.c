int main()
{
    int arr[ 10 ],
        *p = arr;
    const int *q = &arr[ 9 ];

    assert( q - p == 9 );
    assert( p - q == -9 );

    return 0;
}
