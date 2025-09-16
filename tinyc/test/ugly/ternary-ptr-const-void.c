int main()
{
    bool b;
    const bool *p = &b;

    void *q = b ? &b : p;

    return 0;
}
