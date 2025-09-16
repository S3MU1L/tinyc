struct incomplete;

struct s
{
    struct incomplete x;
};

struct incomplete {};

int main()
{
    struct s x;

    return 0;
}
