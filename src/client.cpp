#include "../include/client.h"
#include "../include/exceptions.h"


Client::Client(std::string name, std::string surname, ShoppingList& shoppingList, float probabilityOfActions) : id(clientId++),name(name), surname(surname), shoppingList(shoppingList) , probabilityOfActions(0.5) {
	setProbabilityOfActions(probabilityOfActions);
}

void Client::setName(const std::string newName) {
	name = newName;
}

void Client::setSurame(const std::string newSurame) {
	surname = newSurame;
}

void Client::setShoppingList(const ShoppingList& newShoppingList) {
	shoppingList = newShoppingList;
}
void Client::setProbabilityOfActions(const float newProbabilityOfActions) {
	if (newProbabilityOfActions >= 0 && newProbabilityOfActions <= 1) {
		probabilityOfActions = newProbabilityOfActions;
	} else {
		throw Exceptions::ProbabilityOutOfRange(newProbabilityOfActions);
	}
}

unsigned Client::getId() const {
	return id;
}

std::string Client::getName() const {
	return name;
}

std::string Client::getSurame() const {
	return surname;
}

ShoppingList& Client::getShoppingList() {
	return shoppingList;
}

std::list<ShoppingItem>& Client::getMedicinesList() {
	return shoppingList.getMedicinesList();
}

float Client::getProbabilityOfActions() const {
	return probabilityOfActions;
}

void Client::replaceMedicineOnList(std::shared_ptr<Medicine> oldMedicinePtr, std::shared_ptr<Medicine> newMedicinePtr) {
	shoppingList.replaceMedicineOnList(oldMedicinePtr, newMedicinePtr);
}

void Client::addMedicineToList(std::shared_ptr<Medicine> newMedicinePtr, unsigned numberOfMedicines) {
	shoppingList.addMedicineToList(newMedicinePtr, numberOfMedicines);
}

void Client::removeMedicineFromList(std::shared_ptr<Medicine> oldMedicinePtr) {
	shoppingList.removeMedicineFromList(oldMedicinePtr);
}

void Client::changeMedcineAmount(std::shared_ptr<Medicine> medicinePtr, unsigned newNumberOfMedicines) {
	shoppingList.changeMedcineAmount(medicinePtr, newNumberOfMedicines);
}

Price Client::calculateBruttoPrice() const {
	return calculateNettoPrice() + calculateTax();
}

Price Client::calculateNettoPrice() const {
	return shoppingList.getTotalNettoPrice();
}

void Client::resetClientId() {
	clientId = 1;
}

Client::~Client() {}