#include <iostream>
#include <map>
#include <string>

enum class ArgType {
    INT,
    DOUBLE,
    CHAR,
    STRING,
};

class ArgValue {
public:
    ArgValue()
        : value_(), type_(ArgType::STRING) 
    { }

    ArgValue(const std::string value, const ArgType type)
        : value_(value), type_(type)
    { }

    const std::string& GetValue() const {
        return value_;
    }
private:
    std::string value_;
    ArgType type_;
};

int main(const int argc, const char *argv[]) {
    std::map<std::string, ArgValue> dict;
    // dict["apple"] = ArgValue("1000", ArgType::DOUBLE);
    dict.emplace("apple", ArgValue("1000", ArgType::INT));
    std::cout << dict.at("apple").GetValue() << std::endl;
    return 0;
}