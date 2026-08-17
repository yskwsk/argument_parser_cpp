#ifndef ARGUMENT_PARSER_HPP_
#define ARGUMENT_PARSER_HPP_


#include "arg_type.hpp"
#include "arg_value.hpp"
#include "argument_definition.hpp"


#include <map>
#include <optional>
#include <stdexcept>
#include <string>
#include <vector>


class ArgumentParser {
public:
    ArgumentParser() : program_name_("") {}

    ArgumentParser(const std::string& program_name)
        : program_name_(program_name)
    {}

    void AddOptionalArgument(
        const std::string& name,
        const ArgType type,
        const std::string& help = ""
    ) {
        const std::string option_name = "--" + name;

        optional_definitions_.emplace(
            option_name,
            ArgumentDefinition(
                name,
                type,
                std::nullopt,
                help,
                false
            )
        );
    }

    void AddOptionalArgument(
        const std::string& name,
        const char short_name,
        const ArgType type,
        const std::string& help = ""
    ) {
        const std::string option_name = "--" + name;

        optional_definitions_.emplace(
            option_name,
            ArgumentDefinition(
                name,
                short_name,
                type,
                std::nullopt,
                help,
                false
            )
        );

        short_option_names_.emplace(short_name, option_name);
    }

    template <typename T>
    void AddOptionalArgument(
        const std::string& name,
        const ArgType type,
        const T default_value,
        const std::string& help
    ) {
        const std::string option_name = "--" + name;

        optional_definitions_.emplace(
            option_name,
            ArgumentDefinition(
                name,
                type,
                ArgValue(std::move(default_value)),
                help,
                false
            )
        );
    }

    template <typename T>
    void AddOptionalArgument(
        const std::string& name,
        const char short_name,
        const ArgType type,
        const T default_value,
        const std::string& help
    ) {
        const std::string option_name = "--" + name;

        optional_definitions_.emplace(
            option_name,
            ArgumentDefinition(
                name,
                short_name,
                type,
                ArgValue(std::move(default_value)),
                help,
                false
            )
        );

        short_option_names_.emplace(short_name, option_name);
    }

    void AddFlag(
        const std::string& name,
        const std::string& help = ""
    ) {
        const std::string option_name = "--" + name;

        optional_definitions_.emplace(
            option_name, 
            ArgumentDefinition(
                name,
                ArgType::BOOL,
                ArgValue(false),
                help,
                true
            )
        );
    }

    void AddFlag(
        const std::string& name,
        const char short_name,
        const std::string& help = ""
    ) {
        const std::string option_name = "--" + name;

        optional_definitions_.emplace(
            option_name, 
            ArgumentDefinition(
                name,
                ArgType::BOOL,
                ArgValue(false),
                help,
                true
            )
        );

        short_option_names_.emplace(short_name, option_name);
    }

    void AddPositionalArgument(
        const std::string& name,
        const ArgType type,
        const std::string& help
    ) {
        positional_definitions_.push_back(
            ArgumentDefinition(
                name,
                type,
                std::nullopt,
                help,
                false
            )
        );
    }

    bool Contains(const std::string& name) const {
        return values_.find(name) != values_.end();
    }

    template <typename T>
    T Get(const std::string& name) const {
        const auto it = values_.find(name);
        if (it == values_.end()) {
            throw std::runtime_error("Argument not found: " + name);
        }
        return it->second.GetValue<T>();
    }

    void Parse(const int argc, const char* argv[]);

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

    /**
     * 短いオプジョン引数名と元の(長い)オプション引数名を対応づけるmap変数
     * key: short name
     * value: long name
     */
    std::map<char, std::string> short_option_names_;

    // 実際の値を格納
    std::map<std::string, ArgValue> values_;

    ArgValue ConvertValue(std::string value, const ArgType type);

    bool ContainsOptionalArgument(const std::string& value) const {
        return optional_definitions_.find(value) != optional_definitions_.end();
    }
};

#endif /* ARGUMENT_PARSER_HPP_ */
