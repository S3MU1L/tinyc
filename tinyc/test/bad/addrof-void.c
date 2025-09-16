void foo() {}

int main()
{
    void *p = &foo();
    return 0;
}
