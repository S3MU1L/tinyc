void evil( int *p )
{
    *p = 42;
}

int main()
{
    const int x = 1;
    evil( &x );

    return 0;
}
