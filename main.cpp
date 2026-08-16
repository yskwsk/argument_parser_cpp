#include <iostream>


#include "src/argument_parser.hpp"


// ./a.out input_file output_file --port 8888 --name user --verbose


int main(const int argc, const char* argv[]) {
    ArgumentParser parser("parser test");
    parser.AddPositionalArgument("input", ArgType::STRING, "input file");
    parser.AddPositionalArgument("output", ArgType::STRING, "output file");
    parser.AddOptionalArgument("--port", ArgType::INT, ArgValue(8080), "Server port number");
    parser.AddOptionalArgument("--name", ArgType::STRING, "User name");
    parser.AddFlag("--verbose", "Test verbose");

    parser.Parse(argc, argv);

    std::cout << parser.Get<std::string>("input") << std::endl;
    std::cout << parser.Get<std::string>("output") << std::endl;
    std::cout << parser.Get<int>("--port") << std::endl;
    std::cout << parser.Get<std::string>("--name") << std::endl;
    std::cout << parser.Get<bool>("--verbose") << std::endl;

    return 0;
}
