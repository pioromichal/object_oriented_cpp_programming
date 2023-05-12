#ifndef INDIVIDUAL_CLIENT_H
#define INDIVIDUAL_CLIENT_H

#include "client.h"

#include <string>

class IndividualClient : public Client {
	private:
		static const unsigned taxPercentage = 23;
	public:
		IndividualClient(std::string name, std::string surname, ShoppingList shoppingList, float probabilityOfActions);
		Price calculateTax() const override;
};

#endif