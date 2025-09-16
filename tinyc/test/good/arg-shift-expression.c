unsigned f( unsigned arg1, unsigned arg2, unsigned arg3 )
{
    return 0;
}

int main()
{
    unsigned a = 1;
    f( a, a, a << 1 );
    return 0;
}
