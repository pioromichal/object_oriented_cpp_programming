#include "../include/shopping_list.h"

#include <algorithm>

ShoppingList::ShoppingList() : medicinesList{} {}

void ShoppingList::addMedicineToList(std::shared_ptr<Medicine> newMedicinePtr, unsigned newNumberOfMedicines) {	
	medicinesList.push_back(ShoppingItem(newMedicinePtr, newNumberOfMedicines));
}

void ShoppingList::replaceMedicineInList(std::shared_ptr<Medicine> oldMedicinePtr, std::shared_ptr<Medicine> newMedicinePtr) {
	auto it = std::find_if(medicinesList.begin(), medicinesList.end(), [oldMedicinePtr](const ShoppingItem& medicine) {
		return medicine.getMedicinePtr() == oldMedicinePtr;
		});
		if (it != medicinesList.end()) {
			it->setMedicinePtr(newMedicinePtr);
		}
		else {
			
		}
}

const std::list<ShoppingItem>& ShoppingList::getMedicinesList() {
	return medicinesList;
}