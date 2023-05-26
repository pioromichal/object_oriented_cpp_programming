#ifndef PROI_23L_101_APTEKA_CLIENT_H
#define PROI_23L_101_APTEKA_CLIENT_H

#include "shopping_list.h"

#include <string>
#include <memory>

class Client {
	private:
		inline static unsigned clientId = 1;
	protected:
		unsigned id;
		std::string name;
		std::string surname;
		ShoppingList shoppingList;
		float probabilityOfActions;
	public:
		Client(std::string name, std::string surname, ShoppingList& shoppingList, float probabilityOfActions);

		void setName(const std::string newName);
		void setSurame(const std::string newSurame);
		void setShoppingList(const ShoppingList& newShoppingList);
		void setProbabilityOfActions(const float newProbabilityOfActions);

		unsigned getId() const;
		std::string getName() const;
		std::string getSurame() const;
		ShoppingList& getShoppingList();
		float getProbabilityOfActions() const;
		std::list<ShoppingItem>& getMedicinesList();

		void replaceMedicineOnList(std::shared_ptr<Medicine> oldMedicinePtr, std::shared_ptr<Medicine> newMedicinePtr);
		void addMedicineToList(std::shared_ptr<Medicine> newMedicinePtr, unsigned numberOfMedicines);
		std::list<ShoppingItem>::iterator removeMedicineFromList(std::shared_ptr<Medicine> oldMedicinePtr);
		void changeMedcineAmount(std::shared_ptr<Medicine> medicinePtr, unsigned newNumberOfMedicines);

		Price calculateBruttoPrice() const;
		Price calculateNettoPrice() const;
		virtual Price calculateTax() const = 0;

		static void resetClientId();

		virtual ~Client();
};

#endif //PROI_23L_101_APTEKA_CLIENT_H
