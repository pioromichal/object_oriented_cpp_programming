#include "../include/file_manager.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
using json = nlohmann::json;
FileManager::FileManager(int argc, char **argv) {
    Arguments arguments(argc,argv);
    std::ifstream jsonFile(arguments.pathToJSON());
    if(!jsonFile.is_open()){
        throw std::invalid_argument("Failed to open a file!");
    }
    json data = json::parse(jsonFile);
    std::cout<<data["pi"]<<std::endl;
    if(data["happy"]){
        std::cout<<"Happy!!"<<std::endl;
    }
    else{
        std::cout<<"not"<<std::endl;
    }
    jsonFile.close();
}
