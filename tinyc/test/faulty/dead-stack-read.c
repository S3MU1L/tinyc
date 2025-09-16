int *local()
{
    int x = 66;
    return &x;
}

int main()
{
    int x = *local();

    return 0;
}

