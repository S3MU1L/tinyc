int main()
{
    int x = 0;
    int y = 0;

    while ( x < 10 )
    {
        ++x;
        for ( int i = 0; i < 4; ++i )
        {
            ++y;
            continue;
            x *= 5;
        }
        x *= 7;
        break;
        x *= 3;
    }

    assert( x == 7 );
    assert( y == 4 );

    return 0;
}
