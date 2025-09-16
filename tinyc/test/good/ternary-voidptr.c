int main()
{
    bool b;

    void *vp = &b;
    void *p = b ? &b : vp,
         *q = b ? vp : &b,
         *r = b ? vp : vp;

    return 0;
}
