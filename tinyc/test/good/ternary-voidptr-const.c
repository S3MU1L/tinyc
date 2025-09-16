int main()
{
    bool b;
    const bool *p = &b;

    const void *q = b ? &b : p;

    return 0;
}
