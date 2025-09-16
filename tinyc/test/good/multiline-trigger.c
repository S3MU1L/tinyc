void foo( unsigned *a ) {
    unsigned b = *a;
}

void bar() {
    unsigned b = 3;
    unsigned c = b +
                     5;
}

int main()
{
    assert(
            true
            ==
            1
        );

    unsigned a = 0;
    foo( &a );
    return 0;
}
