void foo() {}

int main()
{
    bool b = true;
    b ? foo() : foo();
    1 ? foo() : foo();

    return 0;
}
