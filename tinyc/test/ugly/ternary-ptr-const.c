int main()
{
    bool b;
    const bool *p = &b;

    bool *q = b ? &b : p;

    return 0;
}
