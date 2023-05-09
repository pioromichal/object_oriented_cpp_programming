#ifndef SHOPPING_ITEM_H
#define SHOPPING_ITEM_H

#include <memory>
#include "medicine.h"

class ShoppingItem :
{
private:
	std::shared_ptr<Medicine> medicinePtr;
	unsigned numberOfMedicines;
public:
	ShoppingItem(std::shared_ptr<Medicine> medicinePtr, unsigned numberOfMedicines);
	void setMedicinePtr(const std::shared_ptr<Medicine> newMedicinePtr);
	void setNumberOfMedicines(const unigned newNumberOfMedicines);
	std::shared_ptr<Medicine> getMedicinePtr() const;
	unigned getNumberOfMedicines() const;
};
#endif