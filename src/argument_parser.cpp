#include "argument_parser.hpp"


#include <algorithm>
#include <iostream>
#include <string>


ArgumentParser::ArgumentParser() : program_name_("") {}


ArgumentParser::ArgumentParser(const std::string& program_name)
    : program_name_(program_name)
{}


void ArgumentParser::AddOptionalArgument(
    const std::string& name,
    const ArgType type,
    const std::string& help
) {
    optional_definitions_.emplace(
        name,
        ArgumentDefinition(
            name,
            type,
            std::nullopt,
            help,
            false
        )
    );
}


void ArgumentParser::AddOptionalArgument(
    const std::string& name,
    const ArgType type,
    const ArgValue& default_value,
    const std::string& help
) {
    optional_definitions_.emplace(
        name,
        ArgumentDefinition(
            name,
            type,
            default_value,
            help,
            false
        )
    );
}


void ArgumentParser::AddFlag(
    const std::string& name,
    const std::string& help
) {
    optional_definitions_.emplace(
        name, 
        ArgumentDefinition(
            name,
            ArgType::BOOL,
            ArgValue(false),
            help,
            true
        )
    );
}


void ArgumentParser::AddPositionalArgument(
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


ArgValue ArgumentParser::ConvertValue(std::string value, const ArgType type) {
    switch (type) {
        case ArgType::INT:
            return ArgValue(std::stoi(value));

        case ArgType::DOUBLE:
            return ArgValue(std::stod(value));

        case ArgType::CHAR:
            if (value.size() != 1) {
                throw std::runtime_error("Invalid char value: " + value);
            }
            return ArgValue(value[0]);

        case ArgType::STRING:
            return ArgValue(value);

        case ArgType::BOOL:
            std::transform(
                value.begin(),
                value.end(),
                value.begin(),
                [](char c) { return std::tolower(c); }
            );

            if (value == "true") {
                return ArgValue(true);
            } else if (value == "false") {
                return ArgValue(false);
            } else {
                throw std::runtime_error("Invalid vool value: " + value);
            }

        default:
            break;
    }

    throw std::runtime_error("Unknown ArgType");
}


void ArgumentParser::Parse(const int argc, const char* argv[]) {
    if (argc < 2) {
        throw std::runtime_error("Missing arguments");
    }

    // Helpの表示
    const std::string name = argv[1];
    if (name == "--help" || name == "-h") {
        PrintHelp();
        std::exit(0);
    } 

    // オプション引数のデフォルト値を設定
    for (const auto& [name, definition] : optional_definitions_) {
        if (definition.default_value_.has_value()) {
            values_.emplace(name, definition.default_value_.value());
        }
    }

    // 位置引数用のインデックス
    std::size_t positional_index = 0;

    // コマンドライン引数の解析
    for (int i = 1; i < argc; ++i) {
        const std::string argument = argv[i];

        // オプション引数
        if (!argument.empty() && argument[0] == '-') {
            const auto it = optional_definitions_.find(argument);
            if (it == optional_definitions_.end()) {
                throw std::runtime_error("Unknown optional argument: " + argument);
            }

            const ArgumentDefinition& definition = it->second;

            // フラグ引数の場合
            if (definition.is_flag_arg_) {
                values_.insert_or_assign(argument, ArgValue(true));
                continue;
            }

            // 値を指定する引数の場合
            if (i + 1 > argc) {
                throw std::runtime_error("Missing value for optinal argument: " + argument);
            }

            // iを一つ進めて値を取得
            const std::string value = argv[++i];
            values_.insert_or_assign(argument, ConvertValue(value, definition.type_));
        }
        // 位置引数
        else {
            if (positional_index >= positional_definitions_.size()) {
                throw std::runtime_error("Too many positional arguments");
            }

            const ArgumentDefinition& definition = positional_definitions_[positional_index];
            values_.insert_or_assign(definition.name_, ConvertValue(argument, definition.type_));
            
            // インデックスを１つ進める
            ++positional_index;
        }
    }

    // 必須引数のチェック
    for (const auto& definition : positional_definitions_) {
        if (!Contains(definition.name_)) {
            std::runtime_error("Missing required argument: " + definition.name_);
        }
    }
}


bool ArgumentParser::Contains(const std::string& name) const {
    if (values_.count(name) > 0) {
        return true;
    }
    return false;
}


const ArgValue& ArgumentParser::GetArgValue(const std::string& name) const {
    return values_.at(name);
}


void ArgumentParser::PrintHelp() const {
    std::cout << "Arguments:\n";

    for (const auto& definition : positional_definitions_) {
        std::cout << " " << definition.name_;
        std::cout << "\n     " << definition.help_ << "\n";
    }

    for (const auto& [name, definition] : optional_definitions_) {
        std::cout << " " << name;

        if (definition.default_value_.has_value()) {
            std::cout << " [default: ";
            if (definition.is_flag_arg_) {
                std::cout << "false";
            } else {
                const auto& value = definition.default_value_.value();
                std::visit(
                    [](const auto& v) { std::cout << v; },
                    value.GetVariant()
                );
            }
            std::cout << "]";
        }

        std::cout << "\n     " << definition.help_ << "\n";
    }
}
