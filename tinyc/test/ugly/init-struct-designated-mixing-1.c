struct s { int x, y; };
int main()
{
    struct s s = { 1, .y = 2 };
    return 0;
}
