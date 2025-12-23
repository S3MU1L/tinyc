struct Point {
    int x;
    int y;
};

int main() {
    struct Point p;
    p.x = 5;
    p.y = p.x + 7;
    return p.y;
}

