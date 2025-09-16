int main()
{
    int a = 1;
    &a;
    while ( a )
    {
        int b = 42;
        &b;
        a -= 1;
        continue;
        int c = 100;
        &c;
    }

    a += 2;
    return 0;
}
