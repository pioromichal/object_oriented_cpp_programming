#include <iostream>
#include "include/file_manager.h"
int main(int argc, char **argv) {
    Simulation simulation = FileManager::simulationFromJson(argc,argv);
    simulation.run();
    return 0;
}
