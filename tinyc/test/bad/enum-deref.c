int main()
{
    int x;
    {
        enum {
            x = 20,
        };

        *x;
    }

    return 0;
}
