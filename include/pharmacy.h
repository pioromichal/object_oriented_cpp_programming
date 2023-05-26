//
// Created by damaia on 31.03.23.
//

#ifndef PROI_23L_101_APTEKA_PHARMACY_H
#define PROI_23L_101_APTEKA_PHARMACY_H

#include "inventory.h"
#include "clients_queue.h"
#include "counters_list.h"
#include "shopping_list.h"
// All medicines:
#include "capsules.h"
#include "drops.h"
#include "ointment.h"
#include "powders.h"
#include "syrup.h"
#include "tablets.h"

class Pharmacy {
private:
    Inventory inventory;
    ClientsQueue queue;
    CountersList counters;
    static Affliction randomAffliction();
    static ActiveSubstance randomActiveSubstance();
    static unsigned  randomMiligrams();
    static Price randomPrice();
    static unsigned randomAmount();
    static unsigned randomNumber();
    static unsigned randomVolume();
    static unsigned randomSachets();
    static float randomArguability();
    static ShoppingList randomShoppingList();
public:
    Pharmacy(int nCounters, int nOpenedCounters);
    void addRandomMedicine(std::string& name);
    void pushNewClient(std::string& firstName,std::string& lastName);
};


#endif //PROI_23L_101_APTEKA_PHARMACY_H
