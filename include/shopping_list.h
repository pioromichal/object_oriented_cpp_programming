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
	void removeMedicineFromList(std::shared_ptr<Medicine> oldMedicinePtr);
	void replaceMedicineOnList(std::shared_ptr<Medicine> oldMedicinePtr, std::shared_ptr<Medicine> newMedicinePtr);
	void changeMedcineAmount(std::shared_ptr<Medicine> medicinePtr, unsigned newNumberOfMedicines);

	unsigned getListSize() const;
	std::list<ShoppingItem>& getMedicinesList();
	Price getTotalNettoPrice() const;
};
#endif