#include <iostream>

struct StructExample {
    int a;
    int b;
    int c;
};

void ShowStructAddress(StructExample &exmaple) {
    std::cout << &exmaple.a << std::endl;
    std::cout << &exmaple.b << std::endl;
    std::cout << &exmaple.c << std::endl;
}

union UnionExample {
    int a;
    int b;
    int c;
};

void ShowUnionAddress(UnionExample &example) {
    std::cout << &example.a << std::endl;
    std::cout << &example.b << std::endl;
    std::cout << &example.c << std::endl;
}

union UnionExample2 {
    int a;
    double b;
};

int main() {
    StructExample s = { 1, 2, 3, };
    ShowStructAddress(s);

    UnionExample u;
    ShowUnionAddress(u);

    u.a = 10;
    std::cout << u.c << std::endl;

    UnionExample2 u2 = { 1 };
    std::cout << u2.b << std::endl;
    u2.b = 26;
    std::cout << u2.a << std::endl;

    return 0;
}
