#include "argument_parser.hpp"


#include <iostream>
#include <string>


void ArgumentParser::AddArgument(
    const std::string& name,
    ArgType type,
    const std::string& help
) {
    definitions_.emplace(
        name,
        ArgumentDefinition{
            type,
            help,
            std::nullopt
        }
    );
}


void ArgumentParser::AddArgument(
    const std::string& name,
    ArgType type,
    const ArgValue& default_value,
    const std::string& help
) {
    definitions_.emplace(
        name,
        ArgumentDefinition{
            type,
            help,
            default_value
        }
    );
}


void ArgumentParser::Parse(int argc, const char* argv[]) {
    // デフォルト値を設定
    for (const auto& [name, definition] : definitions_) {
        if (definition.default_value_.has_value()) {
            values_.emplace(
                name, 
                definition.default_value_.value()
            );
        }
    }

    // コマンドライン引数の解析
    for (int i = 1; i < argc; i += 2) {
        const std::string name = argv[i];

        // 引数が登録されているか確認
        const auto definition = definitions_.find(name);
        if (definition == definitions_.end()) {
            throw std::runtime_error("Unknown argument: " + name);
        }

        // 値が存在するか確認
        if (i + 1 >= argc) {
            throw std::runtime_error("Missing value for argument: " + name);
        }

        const std::string value = argv[i+1];
        const ArgType type = definition->second.type_;

        switch (type) {
            case ArgType::INT:
                values_.insert_or_assign(
                    name, 
                    ArgValue(std::stoi(value))
                );
                break;

            case ArgType::DOUBLE:
                values_.insert_or_assign(
                    name,
                    ArgValue(std::stod(value))
                );
                break;

            case ArgType::CHAR:
                if (value.size() != 1) {
                    throw std::runtime_error("Invalid char value: " + value);
                }
                values_.insert_or_assign(
                    name,
                    ArgValue(value[0])
                );
                break;

            case ArgType::STRING:
                values_.insert_or_assign(
                    name,
                    ArgValue(value)
                );
                break;
            
            default:
                break;
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

    for (const auto& [name, definition] : definitions_) {
        std::cout << " " << name;

        if (definition.default_value_.has_value()) {
            std::cout << " [default: ";
            const auto& value = definition.default_value_.value();
            std::visit(
                [](const auto& v) {
                    std::cout << v;
                },
                value.GetVariant()
            );
            std::cout << "]";
        }

        std::cout << "\n     " << definition.help_ << "\n";
    }
}
