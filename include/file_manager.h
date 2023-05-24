#ifndef PROI_23L_101_APTEKA_FILE_MANAGER_H
#define PROI_23L_101_APTEKA_FILE_MANAGER_H
#include "cxxopts.hpp"
#include "simulation.h"
#include <nlohmann/json.hpp>
#include <vector>
#include <fstream>

struct Names{
    std::vector<std::string> firstNames;
    int fLength = 0;
    std::vector<std::string> lastNames;
    int lLength = 0;
};

class FileManager {
private:
    static std::ifstream verifyPath(const std::string&);
    static std::string arguments(int argc, char** argv);
    static Names namesFromFile(std::ifstream& first, std::ifstream& last);
public:
    static Simiulation simulationFromJson(int argc, char** argv);
};



#endif //PROI_23L_101_APTEKA_FILE_MANAGER_H
