void write( int *p ) { *p = 4; }

int main()
{
    const int x[ 2 ] = { 4, 4 };
    write( ( void * ) ( x + 1 ) );

    return 0;
}
