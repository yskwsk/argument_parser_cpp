#include <iostream>


#include "src/argument_parser.hpp"


int main(const int argc, const char* argv[]) {
    ArgumentParser parser;
    parser.AddArgument("--port", ArgType::INT, ArgValue(8080), "Server port number");
    parser.AddArgument("--name", ArgType::STRING, "User name");
    // parser.PrintHelp();

    parser.Parse(argc, argv);

    std::cout << parser.Get<int>("--port") << std::endl;
    std::cout << parser.Get<std::string>("--name") << std::endl;

    return 0;
}
