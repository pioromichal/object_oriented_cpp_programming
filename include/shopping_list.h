#ifndef SHOPPING_LIST_H
#define SHOPPING_LIST_H

#include <memory>
#include <list>

#include "shopping_item.h"

class ShoppingList
{
private:
	std::list<ShoppingItem> medicinesList;
	Price totalNettoPrice;
public:
	ShoppingList();

	void addMedicineToList(std::shared_ptr<Medicine> newMedicinePtr, unsigned newNumberOfMedicines);
	void replaceMedicineInList(std::shared_ptr<Medicine> oldMedicinePtr, std::shared_ptr<Medicine> newMedicinePtr);

	const std::list<ShoppingItem>& getMedicinesList();
	Price getTotalNettoPrice() const;
};
#endif