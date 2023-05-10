#include "..\include\shopping_item.h"

#include <iostream>

ShoppingItem::ShoppingItem(std::shared_ptr<Medicine> medicinePtr, unsigned numberOfMedicines) : medicinePtr(medicinePtr), numberOfMedicines(numberOfMedicines) {}

void ShoppingItem::setMedicinePtr(const std::shared_ptr<Medicine> newMedicinePtr) {
	medicinePtr = newMedicinePtr;
}

void ShoppingItem::setNumberOfMedicines(const unsigned newNumberOfMedicines) {
	numberOfMedicines = newNumberOfMedicines;
}

std::shared_ptr<Medicine> ShoppingItem::getMedicinePtr() const {
	return medicinePtr;
}

unsigned ShoppingItem::getNumberOfMedicines() const {
	return numberOfMedicines;
}

bool ShoppingItem::operator==(const ShoppingItem& other) const {
	return medicinePtr == other.medicinePtr && numberOfMedicines == other.numberOfMedicines;
}

bool ShoppingItem::operator!=(const ShoppingItem& other) const {
	return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const ShoppingItem& shoppingItem) {
	os << *shoppingItem.medicinePtr << "Number: " << shoppingItem.numberOfMedicines << std::endl << std::endl;
	return os;
}