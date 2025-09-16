int main()
{
    int x = 1;

    if ( x > 0 )
        x = -1;
    else if ( x < 0 )
        x = 2;
    else
        x = 3;

    assert( x == -1 );

    return 0;
}
