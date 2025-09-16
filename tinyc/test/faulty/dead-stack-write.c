int *local()
{
    int x = 66;
    return &x;
}

int main()
{
    *local() = 42;

    return 0;
}

