int main()
{
    bool b;
    const bool *p = &b;

    const bool *q = b ? &b : p;

    return 0;
}
