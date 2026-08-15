#ifndef ARGUMENT_DEFINITION_HPP_
#define ARGUMENT_DEFINITION_HPP_


#include "arg_type.hpp"
#include "arg_value.hpp"


#include <optional>
#include <string>


struct ArgumentDefinition {
    ArgType type_;
    std::string help_;
    std::optional<ArgValue> default_value_;
};

#endif /* ARGUMENT_DEFINITION_HPP_ */
