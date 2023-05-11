#include "../include/individual_client.h"

IndividualClient::IndividualClient(std::string name, std::string surname, ShoppingList shoppingList, float probabilityOfActions) : Client(name, surname, shoppingList, probabilityOfActions) {}

Price IndividualClient::calculateTax() const {
	return calculateNettoPrice() * taxPercentage / 100;
}