int main()
{
    int x;

    {
        enum {
            x = 20,
        };

        x = 30;
    }

    return 0;
}
