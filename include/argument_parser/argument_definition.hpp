#ifndef ARGUMENT_DEFINITION_HPP_
#define ARGUMENT_DEFINITION_HPP_


#include "arg_type.hpp"
#include "arg_value.hpp"


#include <optional>
#include <string>


class ArgumentDefinition {
public:
    ArgumentDefinition(
        std::string name,
        ArgType type,
        std::optional<ArgValue>
        default_value,
        std::string help,
        bool is_frag_arg
    ) : name_(std::move(name)),
        short_name_(std::nullopt),
        type_(type),
        default_value_(default_value),
        help_(std::move(help)),
        is_flag_arg_(is_frag_arg)
    {}

    ArgumentDefinition(
        std::string name,
        char short_name,
        ArgType type,
        std::optional<ArgValue>
        default_value,
        std::string help,
        bool is_frag_arg
    ) : name_(std::move(name)),
        short_name_(short_name),
        type_(type),
        default_value_(default_value),
        help_(std::move(help)),
        is_flag_arg_(is_frag_arg)
    {}

    std::string name_;
    std::optional<char> short_name_;
    ArgType type_;
    std::optional<ArgValue> default_value_;
    std::string help_;
    bool is_flag_arg_;
};

#endif /* ARGUMENT_DEFINITION_HPP_ */
