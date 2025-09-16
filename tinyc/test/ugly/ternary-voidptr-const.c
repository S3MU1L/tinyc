int main()
{
    bool b;

    const void *vp = &b;
    void *p = b ? &b : vp;

    return 0;
}
