#ifndef PROI_23L_101_APTEKA_SIMULATION_H
#define PROI_23L_101_APTEKA_SIMULATION_H

#include <vector>
#include <string>
#include <fstream>
#include "pharmacy.h"

using std::ifstream;
struct Names {
    std::vector<std::string> firstNames;
    int fLength = 0;
    std::vector<std::string> lastNames;
    int lLength = 0;
};
struct Medicines{
    std::vector<std::string> medicineNames;
    int length = 0;
};

class Simulation {
private:
    int numberOfTurns;
    Pharmacy pharmacy;
    Names namesData;
    Medicines medicineData;
public:
    Simulation(int nTurns, int nMedicines, int nCounters, int nOpenedCounters, int nStartingClients, ifstream &firstNames,
               ifstream &lastNames, ifstream &medicineNames);
};


#endif //PROI_23L_101_APTEKA_SIMULATION_H
