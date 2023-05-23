#include "../include/shopping_list.h"

#include "../include/exceptions.h"
#include <algorithm>

ShoppingList::ShoppingList() : medicinesList{}, totalNettoPrice(Price()) {}

void ShoppingList::addMedicineToList(std::shared_ptr<Medicine> newMedicinePtr, unsigned newNumberOfMedicines) {	
	auto it = std::find_if(medicinesList.begin(), medicinesList.end(), [newMedicinePtr](const ShoppingItem& medicine) {
		return medicine.getMedicinePtr() == newMedicinePtr;
		});
	if (it == medicinesList.end()) {
		medicinesList.push_back(ShoppingItem(newMedicinePtr, newNumberOfMedicines));
	}
	else {
		it->increaseNumberOfMedicines(newNumberOfMedicines);
	}
	totalNettoPrice += newMedicinePtr->calculatePrice() * newNumberOfMedicines;
}

void ShoppingList::removeMedicineFromList(std::shared_ptr<Medicine> oldMedicinePtr) {
	auto it = std::find_if(medicinesList.begin(), medicinesList.end(), [oldMedicinePtr](const ShoppingItem& medicine) {
		return medicine.getMedicinePtr() == oldMedicinePtr;
		});
	if (it != medicinesList.end()) {
		totalNettoPrice -= it->calculateTotalPrice();
		medicinesList.erase(it);
	}
	else {
		throw Exceptions::MedicineDoesntExistOnList(oldMedicinePtr->getName());
	}
}

void ShoppingList::replaceMedicineOnList(std::shared_ptr<Medicine> oldMedicinePtr, std::shared_ptr<Medicine> newMedicinePtr) {
	auto it = std::find_if(medicinesList.begin(), medicinesList.end(), [oldMedicinePtr](const ShoppingItem& medicine) {
		return medicine.getMedicinePtr() == oldMedicinePtr;
		});
		if (it != medicinesList.end()) {
			totalNettoPrice -= it->calculateTotalPrice();
			it->setMedicinePtr(newMedicinePtr);
			totalNettoPrice += it->calculateTotalPrice();
		}
		else {
			throw Exceptions::MedicineDoesntExistOnList(oldMedicinePtr->getName());
		}
}

void ShoppingList::changeMedcineAmount(std::shared_ptr<Medicine> medicinePtr, unsigned newNumberOfMedicines) {
	auto it = std::find_if(medicinesList.begin(), medicinesList.end(), [medicinePtr](const ShoppingItem& medicine) {
		return medicine.getMedicinePtr() == medicinePtr;
		});
	if (it != medicinesList.end()) {
		totalNettoPrice -= it->calculateTotalPrice();
		if (newNumberOfMedicines != 0) {
			it->setNumberOfMedicines(newNumberOfMedicines);
			totalNettoPrice += it->calculateTotalPrice();
		} else {
			medicinesList.erase(it);
		}
	}
	else {
		throw Exceptions::MedicineDoesntExistOnList(medicinePtr->getName());
	}
}

unsigned ShoppingList::getListSize() const {
	return medicinesList.size();
}

std::list<ShoppingItem>& ShoppingList::getMedicinesList() {
	return medicinesList;
}

Price ShoppingList::getTotalNettoPrice() const {
	return totalNettoPrice;
}