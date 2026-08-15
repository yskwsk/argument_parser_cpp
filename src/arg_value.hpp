#ifndef ARG_VALUE_HPP_
#define ARG_VALUE_HPP_

#include "arg_type.hpp"

#include <string>
#include <variant>


class ArgValue {
public:
    using ValueType = std::variant<
        int,
        double,
        char,
        std::string
    >;

    ArgValue() = default;

    ArgValue(int value) : value_(value) {}

    ArgValue(double value): value_(value) {}

    ArgValue(char value): value_(value) {}

    ArgValue(std::string value): value_(std::move(value)) {}

    template<typename T>
    const T& GetValue() const {
        return std::get<T>(value_);
    }

    const ValueType& GetVariant() const {
        return value_;
    }

private:
    ValueType value_;
};

#endif /* ARG_VALUE_HPP_ */
