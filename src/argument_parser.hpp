#ifndef ARGUMENT_PARSER_HPP_
#define ARGUMENT_PARSER_HPP_


#include "arg_type.hpp"
#include "arg_value.hpp"
#include "argument_definition.hpp"


#include <map>
#include <optional>
#include <string>
#include <vector>


class ArgumentParser {
public:
    ArgumentParser();

    ArgumentParser(const std::string& program_name);

    void AddOptionalArgument(
        const std::string& name,
        const ArgType type,
        const std::string& help = ""
    );

    void AddOptionalArgument(
        const std::string& name,
        const ArgType type,
        const ArgValue& default_value,
        const std::string& help
    );

    void AddFlag(
        const std::string& name,
        const std::string& help = ""
    );

    void AddPositionalArgument(
        const std::string& name,
        const ArgType type,
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
    std::string program_name_;
    // 位置引数の定義を格納するvector変数
    std::vector<ArgumentDefinition> positional_definitions_;

    /**
     * オプション引数の定義を格納するmap変数
     * key: option_name
     *     ex. --example
     * value: ArgumentDefinition
     */
    std::map<std::string, ArgumentDefinition> optional_definitions_;
    // 実際の値を格納
    std::map<std::string, ArgValue> values_;

    ArgValue ConvertValue(std::string value, const ArgType type);

    bool ContainsOptionalArgument(const std::string& value) const;
};

#endif /* ARGUMENT_PARSER_HPP_ */
