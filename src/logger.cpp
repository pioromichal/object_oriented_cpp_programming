#include "../include/logger.h"
#include <stdexcept>
Logger::Logger(std::string& pathToOutput): pathToOutput(pathToOutput), outputFile(pathToOutput) {
    if(!outputFile.is_open()){
        throw std::invalid_argument("file could not be opened");
    }
}
