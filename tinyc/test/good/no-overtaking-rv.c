int foo( int a ) { return 0; }

int bug( int a, int b ) {
    int p = 0;
    int q = 0;
    int r = 0;

    for( int i = 0; i < 1; ++i ) {
        int u = 0;
        int v = foo( 0 );
        if( u == 0 )
            return 0;
    }
    return 0;
}

int main()
{
    return 0;
}

