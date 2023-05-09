#include "..\include\shopping_item.h"

ShoppingItem::ShoppingItem(std::shared_ptr<Medicine> medicinePtr, unsigned numberOfMedicines) : medicinePtr(medicinePtr), numberOfMedicines(numberOfMedicines) {}

void ShoppingItem::setMedicinePtr(const std::shared_ptr<Medicine> newMedicinePtr) {
	medicinePtr = newMedicinePtr;
}

void ShoppingItem::setNumberOfMedicines(const unigned newNumberOfMedicines) {
	numberOfMedicines = newNumberOfMedicines;
}

std::shared_ptr<Medicine> ShoppingItem::getMedicinePtr() const {
	return medicinePtr;
}

unigned ShoppingItem::getNumberOfMedicines() const {
	return numberOfMedicines;
}
