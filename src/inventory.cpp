//
// Created by damia on 06.04.2023.
//

#include "../include/inventory.h"
#include <exception>
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
        if(medicinePtr->getBasePrice()<medicine->getBasePrice() && this->isMedicineInMagazine(medicinePtr)){
            return medicinePtr;
        }
    }
    throw std::exception();
}

void Inventory::pickMedicine(const std::shared_ptr<Medicine> &medicine) {
    medicine->operator--();
}

bool Inventory::isMedicineInMagazine(const std::shared_ptr<Medicine> &medicine) const {
    return medicine->getAmountInPharmacy()>0;
}

std::shared_ptr<Medicine> Inventory::findRandomMedicine() {
//    return std::shared_ptr<Medicine>();
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distributionAffliction(0,(int)Affliction::Count);
    Affliction affliction = static_cast<Affliction>(distributionAffliction(generator));
    std::uniform_int_distribution<int> distributionMedicine(0,inventory[affliction]->size());
    
}

std::shared_ptr<Medicine> Inventory::findRandomMedicine(Affliction affliction) {
    return std::shared_ptr<Medicine>();
}
