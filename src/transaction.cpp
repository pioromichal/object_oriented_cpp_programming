#include "../include/transaction.h"

#include <chrono>
#include <random>

Transaction::Transaction(Inventory& pharmacyIneventory, std::unique_ptr<Client>& supportedClientPtr, std::unique_ptr<Counter>& currentCounterPtr)
	: pharmacyIneventory(pharmacyIneventory), supportedClientPtr(supportedClientPtr), currentCounterPtr(currentCounterPtr), remainingTime(0), nettoPrice(Price()), bruttoPrice(Price()), taxPrice(Price()) {
	if (currentCounterPtr->isOccupied()) {
	
	}
	else {
		currentCounterPtr->setIsOccupied(true);
	}

	setStartingRemainingTime();

	manageShoppingList();
	
	calculatePrices();

	//logger - podejœcie klienta
}

void Transaction::calculatePrices() {
	this->nettoPrice = supportedClientPtr->calculateNettoPrice();
	this->taxPrice = supportedClientPtr->calculateTax();
	this->bruttoPrice = supportedClientPtr->calculateBruttoPrice();
}

void Transaction::setStartingRemainingTime() {
	this->remainingTime = supportedClientPtr->getShoppingList().getListSize() / 3; //////////
	if (supportedClientPtr->getShoppingList().getListSize() % 3 != 0) {
		this->remainingTime++;
	}
}

void Transaction::manageShoppingList() {
	for (ShoppingItem& medicineOnList : supportedClientPtr->getMedicinesList()) {
		this->randomlyFindSubstitute(medicineOnList);

		if (pharmacyIneventory.isMedicineInMagazine(medicineOnList.getMedicinePtr(), medicineOnList.getNumberOfMedicines())) {
			pharmacyIneventory.pickMedicine(medicineOnList.getMedicinePtr(), medicineOnList.getNumberOfMedicines());
		} else {
			manageLackOfMedicine(medicineOnList);
		}
	}
}

void Transaction::randomlyFindSubstitute(ShoppingItem& medicineOnList) {
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 generator(seed);
	std::bernoulli_distribution distribution(supportedClientPtr->getProbabilityOfActions());
	bool findSubs = distribution(generator);
	if (findSubs) {
		this->remainingTime++;
		std::shared_ptr<Medicine> substitutePtr = pharmacyIneventory.findSubstitute(medicineOnList.getMedicinePtr());
		if (substitutePtr == nullptr) {
			supportedClientPtr->removeMedicineFromList(substitutePtr);
			//logger - nie znaleziono zamiennika
		} else {
			supportedClientPtr->replaceMedicineOnList(medicineOnList.getMedicinePtr(), substitutePtr);
			medicineOnList.setMedicinePtr(substitutePtr);
			//logger - znaleziono zamiennik
		}
	}
}

void Transaction::manageLackOfMedicine(ShoppingItem& medicineOnList) {
	unsigned soldAmount = pharmacyIneventory.howManyInMagazine(medicineOnList.getMedicinePtr());
	unsigned leftAmount = medicineOnList.getNumberOfMedicines() - soldAmount;

	pharmacyIneventory.pickMedicine(medicineOnList.getMedicinePtr(), soldAmount);
	supportedClientPtr->changeMedcineAmount(medicineOnList.getMedicinePtr(), soldAmount);

	//loger - sprzedano jak¹œ iloœæ leków (opcjonalnie)

	std::shared_ptr<Medicine> substitutePtr = pharmacyIneventory.findSubstitute(medicineOnList.getMedicinePtr());
	if (substitutePtr == nullptr) {
		supportedClientPtr->removeMedicineFromList(substitutePtr);
		//logger - nie sprzedano
	}
	else {
		//logger - sprzedano zamienniki
		pharmacyIneventory.pickMedicine(substitutePtr, leftAmount);
		supportedClientPtr->addMedicineToList(substitutePtr, leftAmount);
	}
}


unsigned Transaction::getRemainingTime() const {
	return remainingTime;
}

Price Transaction::getNettoPrice() const {
	return nettoPrice;
}

Price Transaction::getBruttoPrice() const {
	return bruttoPrice;
}

Price Transaction::getTaxPrice() const {
	return taxPrice;
}

bool Transaction::isFinished() const {
	return remainingTime == 0;
}

Transaction& Transaction::operator--() {
	remainingTime -= 1;
	return *this;
}

Transaction::~Transaction() {
	currentCounterPtr->setIsOccupied(false);
	//logger - zakoñczono transakcjê
}
