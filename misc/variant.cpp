#include <iostream>
#include <variant>

void VarinatExample() {
    std::variant<int, double> v1;
    v1 = 42;
    std::cout << std::get<int>(v1) << std::endl;
    v1 = 3.14;
    std::cout << std::get<double>(v1) << std::endl;
    try {
        std::cout << std::get<int>(v1) << std::endl;
    } catch(const std::bad_variant_access& e) {
        std::cerr << e.what() << '\n';
    }
    v1 = 3;
    std::cout << std::get<int>(v1) << std::endl;

    std::visit([](auto& value) {
        std::cout << value << std::endl;
    }, v1);

    v1 = 2.5;
    std::visit([](auto& value) {
        std::cout << value << std::endl;
    }, v1);
}


class A {
public:
    void f() {
        std::cout << "Class A" << std::endl;
    }
};

class B {
public:
    void f() {
        std::cout << "Class B" << std::endl;
    }

    void fB() {
        std::cout << "Class B fB()" << std::endl;
    }
};

class C {
public:
    void f() {
        std::cout << "Class C" << std::endl;
    }
};


void VariantExample2() {
    std::variant<A, B, C> v = A{};
    std::visit([](auto& x) {
        x.f();
    }, v);

    v = B{};
    if (std::holds_alternative<B>(v)) {
        B& b = std::get<B>(v);
        b.f();
        b.fB();
    }

    v = C{};
    std::visit([](auto& x) {
        x.f();
    }, v);
} 

int main() {
    VarinatExample();

    VariantExample2();

    return 0;
}
