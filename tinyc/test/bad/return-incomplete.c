struct s;
struct s foo();

int main()
{
    foo();
    return 0;
}

struct s { int x; };
struct s foo()
{
    struct s s;
    return s;
}

