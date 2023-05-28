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
    return nullptr;
}

void Inventory::pickMedicine(const std::shared_ptr<Medicine> &medicine) {
    if(isMedicineInMagazine(medicine)) {
        medicine->operator--();
    }
}


std::shared_ptr<Medicine> Inventory::findRandomMedicine() {
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> distributionAffliction(0,(int)Affliction::Count - 1);
    auto affliction = static_cast<Affliction>(distributionAffliction(rng));
    return findRandomMedicine(affliction);
}

std::shared_ptr<Medicine> Inventory::findRandomMedicine(Affliction affliction) {
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> distributionMedicine(0,inventory[affliction]->size()-1);
    auto it = inventory[affliction]->begin();
    std::advance(it,distributionMedicine(rng));
    return *it;
}

unsigned Inventory::howManyInMagazine(const std::shared_ptr<Medicine> &medicine) const {
    return medicine->getAmountInPharmacy();
}

void Inventory::pickMedicine(const std::shared_ptr<Medicine> &medicine, int number) {
    for (unsigned char i =0;i<number;i++){
        medicine->operator--();
    }
}
bool Inventory::isMedicineInMagazine(const std::shared_ptr<Medicine> &medicine) const {
    return medicine->getAmountInPharmacy()>0;
}
bool Inventory::isMedicineInMagazine(const std::shared_ptr<Medicine> &medicine, int number) const {
    return medicine->getAmountInPharmacy()>number;

}

int Inventory::numberOfMedicines() {
    char numberOfAfflictions = (char) Affliction::Count;
    int result = 0;
    for (char i = 0; i < numberOfAfflictions; i++) {
        result += numberOfMedicines(static_cast<Affliction>(i));
    }
    return result;
}
int Inventory::numberOfMedicines(Affliction affliction) {
    return inventory[affliction]->size();;
}

std::shared_ptr<Medicine> Inventory::findGeneralSubstitute(const std::shared_ptr<Medicine> &medicine) {
    Affliction affliction = medicine->getAfflication();
    for(auto medicinePtr:*inventory[affliction]){
        if(this->isMedicineInMagazine(medicinePtr)){
            return medicinePtr;
        }
    }
    return nullptr;
}

void Inventory::addNewMedicine(std::shared_ptr<Medicine> medicine) {
    Affliction affliction = medicine->getAfflication();
    inventory[affliction]->insert(std::move(medicine));
}