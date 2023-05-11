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
		void setProbabilityOfActions(const float setProbabilityOfActions);

		std::string getName() const;
		std::string getSurame() const;
		ShoppingList& getShoppingList() const;
		float getProbabilityOfActions() const;

		void replaceMedicineOnList(std::shared_ptr<Medicine> oldMedicinePtr, std::shared_ptr<Medicine> newMedicinePtr);
		void addMedicineToList(std::shared_ptr<Medicine> newMedicinePtr, unsigned numberOfMedicines);

		Price calculateBruttoPrice() const;
		Price calculateNettoPrice() const;
		virtual Price calculateTax() const = 0;

		virtual ~Client();
};


// w shopping list stworzyæ pole przechowuj¹ce total netto price i aktualizuj¹ce je przy ka¿dym dodwaniu lub zamienianiu produktu
//


#endif //PROI_23L_101_APTEKA_CLIENT_H
