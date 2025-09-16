int main()
{
    bool b;

    bool *p = b ? &b : NULL,
         *q = b ? NULL : &b,
         *r = b ? NULL : NULL;

    return 0;
}
