#ifndef PROI_23L_101_APTEKA_TRANSACTION_H
#define PROI_23L_101_APTEKA_TRANSACTION_H

#include "client.h"
#include "counter.h"
#include "inventory.h"
#include <memory>

class Transaction {
	private:
		Inventory& pharmacyIneventory;
		std::unique_ptr<Client>& supportedClientPtr;
		std::unique_ptr<Counter>& currentCounterPtr;
		unsigned remainingTime;
		Price nettoPrice;
		Price bruttoPrice;
		Price taxPrice;
		
		void calculatePrices();
		void setStartingRemainingTime();
		void manageShoppingList();
		void randomlyFindSubstitute(ShoppingItem& medicineOnList);
		void manageLackOfMedicine(ShoppingItem& medicineOnList);

	public:
		Transaction(Inventory& pharmacyIneventory, std::unique_ptr<Client>& supportedClientPtr, std::unique_ptr<Counter>& currentCounterPtr);
		bool isFinished() const;
		Transaction& operator--();
		unsigned getRemainingTime() const;
		Price getNettoPrice() const;
		Price getBruttoPrice() const;
		Price getTaxPrice() const;
		~Transaction();
};


#endif //PROI_23L_101_APTEKA_TRANSACTION_H

