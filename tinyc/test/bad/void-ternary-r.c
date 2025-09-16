void foo() {}

int main()
{
    bool b = true;
    b ? 42 : foo();
    return 0;
}
