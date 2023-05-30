#ifndef PROI_23L_101_APTEKA_SIMULATION_H
#define PROI_23L_101_APTEKA_SIMULATION_H

#include <memory>
#include <vector>
#include <string>
#include <fstream>
#include <random>
#include "inventory.h"
#include "transaction.h"
#include "pharmacy.h"
#include "logger.h"
#include "messages.h"

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
    unsigned numberOfTurns;
    unsigned maxNumOfTurns;
    Pharmacy pharmacy;
    Names namesData;
    Medicines medicineData;
    std::list<std::unique_ptr<Transaction>> currentTransactions;
    std::mt19937 generator;
    Logger logger;

    void pushNewClients();
    void assigneClientsToWindows();
    void manageCountersOpening();
    void pushRandomClient();
    void addRandomMedicineToInventory();
    ShoppingList generateRandomShoppingList();
    std::string& generateRandomName();
    std::string& generateRandomSurname();
    std::string& generateRandomMedicineName();
    Affliction generateRandomAffliction();
    ActiveSubstance generateRandomActiveSubstance();
    unsigned generateRandomVolume();
    unsigned generateRandomNumber();
    unsigned generateRandomSachets();
    unsigned generateRandomAmount();
    unsigned generateRandomMiligrams();
    Price generateRandomPrice();
    void decrementTransactions();
    void releaseCounters();
    Simulation& operator++();

public:
    Simulation(int nTurns, int nMedicines, int nCounters, int nOpenedCounters, int nStartingClients,
               std::string &outputPath, ifstream &firstNames, ifstream &lastNames, ifstream &medicineNames);
    void run();
};



#endif //PROI_23L_101_APTEKA_SIMULATION_H
