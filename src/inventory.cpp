//
// Created by damia on 06.04.2023.
//

#include "../include/inventory.h"
#include <stdexcept>
#include <random>

Inventory::Inventory(){
    char numberOfAfflictions = (char)Affliction::Count;
    for(char i = 0;i<numberOfAfflictions;i++){
        inventory[static_cast<Affliction>(i)] = std::make_unique<std::set<std::shared_ptr<Medicine>>>();
    }
}

void Inventory::addMedicine(std::unique_ptr<Medicine> medicine) {
    Affliction affliction = medicine->getAfflication();
    inventory[affliction]->insert(std::move(medicine));
}

std::shared_ptr<Medicine> Inventory::findSubstitute(const std::shared_ptr<Medicine> &medicine){
    Affliction affliction = medicine->getAfflication();
    for(auto medicinePtr:*inventory[affliction]){
        if(medicinePtr->calculatePrice()<medicine->calculatePrice() && this->isMedicineInMagazine(medicinePtr)){
            return medicinePtr;
        }
    }
    throw std::invalid_argument("");
}

void Inventory::pickMedicine(const std::shared_ptr<Medicine> &medicine) {
    if(isMedicineInMagazine(medicine)) {
        medicine->operator--();
    }
}

bool Inventory::isMedicineInMagazine(const std::shared_ptr<Medicine> &medicine) const {
    return medicine->getAmountInPharmacy()>0;
}

std::shared_ptr<Medicine> Inventory::findRandomMedicine() {
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distributionAffliction(0,(int)Affliction::Count);
    Affliction affliction = static_cast<Affliction>(distributionAffliction(generator));
    return findRandomMedicine(affliction);
}

std::shared_ptr<Medicine> Inventory::findRandomMedicine(Affliction affliction) {
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distributionMedicine(0,inventory[affliction]->size());
    auto it = inventory[affliction]->begin();
    std::advance(it,distributionMedicine(generator));
    return *it;
}
#ifdef TESTING_ENV
void Inventory::addNewMedicine(std::shared_ptr<Medicine> medicine) {
    Affliction affliction = medicine->getAfflication();
    inventory[affliction]->insert(std::move(medicine));
}

int Inventory::numberOfMedicines() {
    char numberOfAfflictions = (char)Affliction::Count;
    int result = 0;
    for(char i = 0;i<numberOfAfflictions;i++){
        result+= numberOfMedicines(static_cast<Affliction>(i));
    }
    return result;
}

int Inventory::numberOfMedicines(Affliction affliction) {
    return inventory[affliction]->size();;
}



#endif
