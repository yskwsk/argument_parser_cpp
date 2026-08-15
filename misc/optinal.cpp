#include <iostream>
#include <optional>



void OptionalExample() {
    // 空の場合
    std::optional<int> empty;
    // std::cout << empty.value() << std::endl;
    if (empty.has_value()) {
        std::cout << empty.value() << std::endl;
    } else {
        std::cout << "値が存在しません" << std::endl;
    }

    try {
        int val = empty.value();
        std::cout << val << std::endl;
    } catch (const std::bad_optional_access& e) {
        std::cout << "値が存在しません" << std::endl;
    }

    // nulloptを利用した明示的な空の初期化
    std::optional<double> explicit_empty = std::nullopt;
    if (explicit_empty.has_value()) {
        std::cout << explicit_empty.value() << std::endl;
    } else {
        std::cout << "値が存在しません" << std::endl;
    }

    // 値を持つ場合1
    std::optional<double> value = 42;
    if (value.has_value()) {
        std::cout << value.value() << std::endl;
    } else {
        std::cout << "値が存在しません" << std::endl;
    }
}


class OptionalExampleClass {
public:
    int GetValue() const {
        return value_.value_or(42);
    }

    void SetValue(const int value) {
        if (value > 0) {
            value_ = std::optional<int>(value);
        } else {
            value_ = std::nullopt;
        }
    }
private:
    std::optional<int> value_;
};


void OptionalExample2() {
    OptionalExampleClass opt;
    std::cout << opt.GetValue() << std::endl;

    opt.SetValue(1000);
    std::cout << opt.GetValue() << std::endl;
}


int main() {
    OptionalExample();
    OptionalExample2();
    return 0;
}
