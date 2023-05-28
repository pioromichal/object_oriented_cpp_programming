#ifndef PROI_23L_101_APTEKA_FILE_MANAGER_H
#define PROI_23L_101_APTEKA_FILE_MANAGER_H
#include "cxxopts.hpp"
#include "simulation.h"
#include <nlohmann/json.hpp>
#include <vector>
#include <fstream>


class FileManager {
private:
    static std::ifstream verifyPath(const std::string&);
    static std::string arguments(int argc, char** argv);
public:
    static Simulation simulationFromJson(int argc, char** argv);
    static Names namesFromFile(std::ifstream& first, std::ifstream& last);
    static Medicines medicineNamesFromFile(std::ifstream& medicineFile);
};



#endif //PROI_23L_101_APTEKA_FILE_MANAGER_H
