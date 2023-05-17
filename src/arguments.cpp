#include "../include/arguments.h"
#include <iostream>
Arguments::Arguments(int argc, char** argv) {
    cxxopts::Options options("Symulacja apteki");
    options.add_options()("h,help","Print help")
                            ("path","Path to config JSON file",cxxopts::value<std::string>());
    results = options.parse(argc,argv);
    if (results.count("help"))
    {
        std::cout << options.help() << std::endl;
        exit(0);
    }
}

std::string Arguments::pathToJSON() {
    return results["path"].as<std::string>();
}
