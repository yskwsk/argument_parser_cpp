/**
 * cd examples
 * g++ -std=c++17 main.cpp -I../include -L../build -largument_parser -o parser_test
 * 
 */
#include <argument_parser/argument_parser.hpp>
#include <iostream>


int main(const int argc, const char* argv[]) {
    ArgumentParser parser("parser test");

    parser.AddPositionalArgument("input", ArgType::STRING, "input file");
    parser.AddPositionalArgument("output", ArgType::STRING, "output file");
    parser.AddOptionalArgument("port", 'p', ArgType::INT, 8080, "Server port number");
    parser.AddOptionalArgument("name", ArgType::STRING, "User name");
    parser.AddFlag("verbose", 'v', "Test verbose");
    parser.Parse(argc, argv);

    std::cout << parser.Get<std::string>("input") << std::endl;
    std::cout << parser.Get<std::string>("output") << std::endl;
    std::cout << parser.Get<int>("port") << std::endl;
    std::cout << parser.Get<std::string>("name") << std::endl;
    std::cout << parser.Get<bool>("verbose") << std::endl;

    return 0;
}
