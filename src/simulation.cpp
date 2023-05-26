#include "../include/simulation.h"
#include "../include/file_manager.h"

Simulation::Simulation(int nTurns, int nMedicines, int nCounters, int nOpenedCounters, int nStartingClients,
                       ifstream &firstNames,
                       ifstream &lastNames, ifstream &medicineNames) : numberOfTurns(nTurns), namesData(
        FileManager::namesFromFile(firstNames, lastNames)),
                                                                       medicineData(FileManager::medicineNamesFromFile(
                                                                               medicineNames)),
                                                                       pharmacy(nCounters, nOpenedCounters) {

    for (int i = 0; i < nStartingClients; i++) {
        //TODO function generating data from namesData
        pharmacy.pushNewClient(randomName(), randomSurname());
    }

    for (int i = 0; i < nMedicines; i++) {
        //TODO function generating data from medicineData
        pharmacy.addRandomMedicine(randomMedicineName());
    }
}

std::string &Simulation::randomName() {
    return (std::string &) "Place";
}

std::string &Simulation::randomSurname() {
    return (std::string &) "holder";
}

std::string &Simulation::randomMedicineName() {
    return (std::string &) "Hatered";
}
