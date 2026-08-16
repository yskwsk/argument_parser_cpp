#ifndef ARGUMENT_PARSER_HPP_
#define ARGUMENT_PARSER_HPP_


#include "arg_type.hpp"
#include "arg_value.hpp"
#include "argument_definition.hpp"


#include <map>
#include <optional>
#include <string>


class ArgumentParser {
public:
    void AddArgument(
        const std::string& name,
        ArgType type,
        const std::string& help
    );

    void AddArgument(
        const std::string& name,
        ArgType type,
        const ArgValue& default_value,
        const std::string& help
    );

    void Parse(const int argc, const char* argv[]);

    bool Contains(const std::string& name) const;

    const ArgValue& GetArgValue(const std::string& name) const;

    template <typename T>
    T Get(const std::string& name) const {
        return GetArgValue(name).GetValue<T>();
    }

    void PrintHelp() const;
private:
    // 引数の定義を格納するmap変数
    std::map<std::string, ArgumentDefinition> definitions_;
    // 実際の値を格納
    std::map<std::string, ArgValue> values_;
};

#endif /* ARGUMENT_PARSER_HPP_ */
