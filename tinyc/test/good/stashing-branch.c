int main()
{
    int a = 1;
    &a;
    if ( a )
    {
        int b;
        &b;
    }
    else
    {
        int b, c;
        &b, &c;
    }
    a += 2;

    return 0;
}
