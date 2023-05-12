#ifndef SHOPPING_ITEM_H
#define SHOPPING_ITEM_H

#include "medicine.h"
#include "price.h"

#include <memory>

class ShoppingItem {
private:
	std::shared_ptr<Medicine> medicinePtr;
	unsigned numberOfMedicines;
public:
	ShoppingItem(std::shared_ptr<Medicine> medicinePtr, unsigned numberOfMedicines);

	void setMedicinePtr(const std::shared_ptr<Medicine> newMedicinePtr);
	void setNumberOfMedicines(const unsigned newNumberOfMedicines);

	std::shared_ptr<Medicine> getMedicinePtr() const;
	unsigned getNumberOfMedicines() const;

	void increaseNumberOfMedicines(unsigned number);
	Price calculateTotalPrice() const;

	bool operator==(const ShoppingItem& other) const;
	bool operator!=(const ShoppingItem& other) const;

	friend std::ostream& operator<<(std::ostream& os, const ShoppingItem& shoppingItem);
};

std::ostream& operator<<(std::ostream& os, const ShoppingItem& shoppingItem);

#endif