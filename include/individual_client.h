#ifndef INDIVIDUAL_CLIENT_H
#define INDIVIDUAL_CLIENT_H

#include "client.h"

#include <string>

class IndividualClient : Client {
private:
	static const unsigned tax = 23;
public:
	IndividualClient(std::string name, std::string surname, ShoppingList shoppingList, float probabilityOfActions);
	Price calculateTax() override;
};

#endif