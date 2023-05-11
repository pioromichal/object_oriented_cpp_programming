#ifndef BUSINESS_CLIENT_H
#define BUSINESS_CLIENT_H

#include "client.h"

#include <string>

class BusinessClient : Client {
private:
	static const unsigned tax = 8;
public:
	BusinessClient(std::string name, std::string surname, ShoppingList shoppingList, float probabilityOfActions);
	Price calculateTax() override;
};


#endif