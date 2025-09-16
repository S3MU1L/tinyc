int main()
{
    int x = 42;
    const int *p = &x;

    *p = 60;

    return 0;
}
