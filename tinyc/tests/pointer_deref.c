int main() {
    int a = 40;
    int* p = &a;
    *p = *p + 2;
    return a;
}
