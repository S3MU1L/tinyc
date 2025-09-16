void recurse( int x )
{
    if ( x == 0 )
        return;

    char fill[ 1024 ];
    recurse( x - 1 );
}

int main()
{
    recurse( 16 );
    return 0;
}
