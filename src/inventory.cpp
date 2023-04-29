//
// Created by damia on 06.04.2023.
//

#include "../include/inventory.h"

Inventory::Inventory() = default;

void Inventory::addMedicine(std::unique_ptr<Medicine> &) {

}

std::shared_ptr<Medicine> Inventory::findSubstitute(const std::shared_ptr<Medicine> &medicine) const {
    return std::shared_ptr<Medicine>();
}

void Inventory::pickMedicine(const std::shared_ptr<Medicine> &medicine) {

}

bool Inventory::isMedicineInMagazine(const std::shared_ptr<Medicine> &medicine) const {
    return false;
}

std::shared_ptr<Medicine> Inventory::findRandomMedicine() {
    return std::shared_ptr<Medicine>();
}

std::shared_ptr<Medicine> Inventory::findRandomMedicine(Effect effect) {
    return std::shared_ptr<Medicine>();
}
