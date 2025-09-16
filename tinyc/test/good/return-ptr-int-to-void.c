struct st { int x; };

void* foo()
{
    int *p;
    return p;
}

int main()
{
    foo();
    return 0;
}
