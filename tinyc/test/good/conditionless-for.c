int main()
{
    int x = 0;

    for ( ;; )
    {
        x++;
        break;
    }

    assert( x == 1 );

    for ( ;; x = 100 )
    {
        x++;
        break;
    }

    assert( x == 2 );

    for ( x = 5 ;; x = 100 )
    {
        x++;
        break;
    }

    assert( x == 6 );

    for ( x = 10 ;; )
    {
        x++;
        break;
    }

    assert( x == 11 );

    for ( int y = 42 ;; )
    {
        x = y++;
        break;
    }

    assert( x == 42 );


    for ( int y = 20 ;; y *= 10 )
    {
        x = y++;
        break;
    }

    assert( x == 20 );

    return 0;
}
