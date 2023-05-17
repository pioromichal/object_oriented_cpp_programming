#ifndef PROI_23L_101_APTEKA_ARGUMENTS_H
#define PROI_23L_101_APTEKA_ARGUMENTS_H
#include "cxxopts.hpp"
#include <memory>
class Arguments {
private:
    cxxopts::ParseResult results;
public:
    Arguments(int argc, char** argv);
    std::string pathToJSON();

};


#endif //PROI_23L_101_APTEKA_ARGUMENTS_H
