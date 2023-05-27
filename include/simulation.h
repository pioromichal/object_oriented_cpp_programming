#ifndef PROI_23L_101_APTEKA_SIMULATION_H
#define PROI_23L_101_APTEKA_SIMULATION_H

#include <memory>
#include <vector>
#include <string>
#include <fstream>
#include "inventory.h"
#include "transaction.h"
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
    unsigned maksNumOfTurns;
    Pharmacy pharmacy;
    Names namesData;
    Medicines medicineData;
    std::list<std::unique_ptr<Transaction>> currentTransactions;
    std::string& randomName();
    std::string& randomSurname();
    std::string& randomMedicineName();

public:
    Simulation(int nTurns, int nMedicines, int nCounters, int nOpenedCounters, int nStartingClients, ifstream &firstNames,
               ifstream &lastNames, ifstream &medicineNames);
    void simulate();
    void pushNewClients();
    void assigneClientsToWindows();
    void manageCountersOpening();
    void pushRandomClient();
    ShoppingList generateRandomShoppingList();
    std::string generateRandomName();
    std::string generateRandomSurname();
    void decrementTransactionsAndReleaseCounters();
    Simulation& operator++();
};



#endif //PROI_23L_101_APTEKA_SIMULATION_H
