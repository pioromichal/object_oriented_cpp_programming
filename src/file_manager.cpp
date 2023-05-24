#include <iostream>
#include "../include/file_manager.h"
#include <fstream>
#include <stdexcept>
#include <algorithm>
using json = nlohmann::json;

Simiulation FileManager::simulationFromJson(int argc, char **argv) {

    std::string path  = arguments(argc,argv);
    std::ifstream jsonFile(path);
    if(!jsonFile.is_open()){
        throw std::invalid_argument("Failed to open a file!");
    }
    //Prawdopodobnie trzeba to otoczyć catchem sprawdzając czy dane istnieją w JSON
    json data = json::parse(jsonFile);
    std::ifstream firstNames = verifyPath(data["pathToFirstNameList"]);
    std::ifstream lastNames = verifyPath(data["pathToLastNameList"]);
    std::ifstream medicineNames = verifyPath(data["pathToMedicineNameList"]);
    int nTurns = data["nTurns"];
    int nCounters = data["nCounters"];
    int nOpenedCounters = data["nOpenedCounters"];
    Names names = namesFromFile(firstNames,lastNames);
    firstNames.close();
    lastNames.close();
}

std::ifstream FileManager::verifyPath(const std::string& path) {
    std::ifstream file(path);
    if(!file.is_open()){
        throw std::invalid_argument("Failed to open a file!"+path);
        exit(2);
    }
    else{
        return file;
    }
}

std::string FileManager::arguments(int argc, char **argv) {
    cxxopts::Options options("Symulacja apteki");
    options.add_options()("h,help","Print help")
            ("path","Path to config JSON file",cxxopts::value<std::string>());
    auto results = options.parse(argc,argv);
    if (results.count("help"))
    {
        std::cout << options.help() << std::endl;
        exit(0);
    }
    return results["path"].as<std::string>();
}

Names FileManager::namesFromFile(std::ifstream& first, std::ifstream& last) {
    Names result;
    std::string line;
    while (std::getline(first, line))
        ++result.fLength;
    while (std::getline(last,line))
        ++result.lLength;
    result.firstNames.reserve(result.fLength);
    result.lastNames.reserve(result.lLength);
    first.clear();
    first.seekg(0);
    while (std::getline(first, line)) {
        line.erase(remove(line.begin(), line.end(), '\r'), line.end());
        result.firstNames.push_back(line);
    }
    last.clear();
    last.seekg(0);
    while (std::getline(last, line)){
        line.erase(remove(line.begin(), line.end(), '\r'), line.end());
        result.lastNames.push_back(line);}
    return result;
}

