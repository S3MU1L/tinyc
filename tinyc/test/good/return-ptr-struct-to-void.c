struct st { int x; };

void* foo()
{
    struct st s;
    return &s;
}

int main()
{
    foo();
    return 0;
}
