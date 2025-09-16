void write( int *p ) { *p = 4; }

int main()
{
    const int x = 4;
    write( ( void * ) &x );

    return 0;
}
