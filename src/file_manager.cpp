#include <iostream>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <regex>
#include "../include/file_manager.h"

using json = nlohmann::json;

Simulation FileManager::simulationFromJson(int argc, char **argv) {
    std::string path  = arguments(argc,argv);
    std::ifstream jsonFile(path);
    if(!jsonFile.is_open()){
        throw Exceptions::WrongJSONPath(path);
    }
    try {
        json data = json::parse(jsonFile);
        std::ifstream firstNames = verifyPath(data["pathToFirstNameList"]);
        std::ifstream lastNames = verifyPath(data["pathToLastNameList"]);
        std::ifstream medicineNames = verifyPath(data["pathToMedicineNameList"]);
        int nTurns = data["nTurns"];
        int nCounters = data["nCounters"];
        int nOpenedCounters = data["nOpenedCounters"];
        if (nCounters < nOpenedCounters) {
          throw Exceptions::IncorrectDataFromJSON();
        }
        int nStartingClients = data["nStartingClients"];
        int nMedicines = data["nMedicinesToCreate"];
        std::string outputPath = data["outputPath"];
        verifyOutputPath(outputPath);

        Simulation simulation(nTurns, nMedicines, nCounters, nOpenedCounters, nStartingClients, outputPath, firstNames,
                              lastNames, medicineNames);
        firstNames.close();
        lastNames.close();
        medicineNames.close();
        jsonFile.close();
        return simulation;
    }
    catch (json::type_error&){
        std::cout<<"Failed to read data from the file"<<std::endl;
        exit(2);
    }
}

std::ifstream FileManager::verifyPath(const std::string& path) {
    std::ifstream file(path);
    if(!file.is_open()){
        throw std::invalid_argument("Failed to open a file! "+path);
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

Medicines FileManager::medicineNamesFromFile(ifstream &medicineFile) {
    Medicines result;
    std::string line;
    while (std::getline(medicineFile, line))
        ++result.length;
    result.medicineNames.reserve(result.length);
    medicineFile.clear();
    medicineFile.seekg(0);
    while (std::getline(medicineFile,line)){
        line.erase(remove(line.begin(), line.end(), '\r'), line.end());
        result.medicineNames.push_back(line);
    }
    return result;
}

void FileManager::verifyOutputPath(std::string & path) {
    std::regex logPattern(".*.log$");
    std::regex directoryPattern("\/$");
    bool isLog = std::regex_search(path,logPattern);
    bool isDirectory = std::regex_search(path,directoryPattern);
    if(isLog){
        return;
    }
    else if(isDirectory){
        path+="output.log";
    }
    else{
        throw std::invalid_argument("wrong path to output");
    }
}

