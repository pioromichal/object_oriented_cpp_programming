#include "../include/business_client.h"

BusinessClient::BusinessClient(std::string name, std::string surname, ShoppingList shoppingList, float probabilityOfActions) : Client(name, surname, shoppingList, probabilityOfActions) {}

Price BusinessClient::calculateTax() const {
	return calculateNettoPrice() * taxPercentage / 100;
}
