struct st { int x; };

struct st* foo()
{
    void *p;
    return p;
}

int main()
{
    foo();
    return 0;
}
