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
            break;
            x *= 5;
        }
        continue;
        x *= 5;
    }

    assert( x == 10 );
    assert( y == 10 );

    return 0;
}
