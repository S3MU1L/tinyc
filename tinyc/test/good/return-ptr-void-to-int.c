struct st { int x; };

int* foo()
{
    void *p;
    return p;
}

int main()
{
    foo();
    return 0;
}
