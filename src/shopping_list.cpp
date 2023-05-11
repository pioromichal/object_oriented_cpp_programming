#include "../include/shopping_list.h"

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

void ShoppingList::replaceMedicineInList(std::shared_ptr<Medicine> oldMedicinePtr, std::shared_ptr<Medicine> newMedicinePtr) {
	auto it = std::find_if(medicinesList.begin(), medicinesList.end(), [oldMedicinePtr](const ShoppingItem& medicine) {
		return medicine.getMedicinePtr() == oldMedicinePtr;
		});
		if (it != medicinesList.end()) {
			totalNettoPrice -= it->calculateTotalPrice();
			it->setMedicinePtr(newMedicinePtr);
			totalNettoPrice += it->calculateTotalPrice();
		}
		else {
			
		}
}

const std::list<ShoppingItem>& ShoppingList::getMedicinesList() {
	return medicinesList;
}

Price ShoppingList::getTotalNettoPrice() const {
	return totalNettoPrice;
}