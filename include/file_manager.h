//
// Created by damia on 06.04.2023.
//

#ifndef PROI_23L_101_APTEKA_FILE_MANAGER_H
#define PROI_23L_101_APTEKA_FILE_MANAGER_H
#include <nlohmann/json.hpp>
#include "arguments.h"
using json = nlohmann::json;

class FileManager {
public:
    FileManager(int argc, char** argv);
};


#endif //PROI_23L_101_APTEKA_FILE_MANAGER_H
