int main()
{
    int arr[ 10 ],
        *p = arr;
    const int *q = &arr[ 9 ];

    assert( q != p );
    assert( q > p );

    return 0;
}
