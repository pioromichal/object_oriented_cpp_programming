#include "../include/transaction.h"
#include "../include/exceptions.h"
#include <chrono>
#include <random>

Logger* Transaction::logger = nullptr;

Transaction::Transaction(Inventory& pharmacyIneventory, std::unique_ptr<Client> supportedClientPtr, std::unique_ptr<Counter>& currentCounterPtr)
	: pharmacyIneventory(pharmacyIneventory), supportedClientPtr(std::move(supportedClientPtr)), currentCounterPtr(currentCounterPtr), remainingTime(0), nettoPrice(Price()), bruttoPrice(Price()), taxPrice(Price()) {
	if (currentCounterPtr->isOccupied()) {
		Exceptions::TransactionGotWrongCounter();
	}
	else {
		currentCounterPtr->setIsOccupied(true);
	}

	setStartingRemainingTime();
    (*logger).operator<<(Messages::clientCameToCounter(this->supportedClientPtr->getId(), currentCounterPtr->getId(), this->supportedClientPtr->getShoppingList().getListSize()))<<std::endl;

	manageShoppingList();
	
	calculatePrices();

}

void Transaction::calculatePrices() {
	this->nettoPrice = supportedClientPtr->calculateNettoPrice();
	this->taxPrice = supportedClientPtr->calculateTax();
	this->bruttoPrice = supportedClientPtr->calculateBruttoPrice();
}

void Transaction::setStartingRemainingTime() {
	this->remainingTime = supportedClientPtr->getShoppingList().getListSize() / 3;
	if (supportedClientPtr->getShoppingList().getListSize() % 3 != 0) {
		this->remainingTime++;
	}
}

void Transaction::manageShoppingList() {
	for (auto medicineOnListIt = supportedClientPtr->getMedicinesList().begin(); medicineOnListIt != supportedClientPtr->getMedicinesList().end();) {
		this->randomlyFindSubstitute(medicineOnListIt);

		if (pharmacyIneventory.isMedicineInMagazine(medicineOnListIt->getMedicinePtr(), medicineOnListIt->getNumberOfMedicines())) {
			pharmacyIneventory.pickMedicine(medicineOnListIt->getMedicinePtr(), medicineOnListIt->getNumberOfMedicines());
			medicineOnListIt++;
		}
		else {
			remainingTime++;
			unsigned soldAmount = pharmacyIneventory.howManyInMagazine(medicineOnListIt->getMedicinePtr());
			if (soldAmount != 0) {
                unsigned amountOfMedicine = medicineOnListIt->getNumberOfMedicines();
				supportedClientPtr->changeMedcineAmount(medicineOnListIt->getMedicinePtr(), soldAmount);
				pharmacyIneventory.pickMedicine(medicineOnListIt->getMedicinePtr(), soldAmount);
                (*logger).operator<<(Messages::changedNumberOfMedicines(*medicineOnListIt,amountOfMedicine))<<std::endl;
				medicineOnListIt++;

			} else {
				medicineOnListIt = supportedClientPtr->removeMedicineFromList(medicineOnListIt->getMedicinePtr());
                //logger - brak leku (nie sprzedano)
                (*logger).operator<<(Messages::failedToSellMedicine(*medicineOnListIt))<<std::endl;
            }
		}
	}
}

void Transaction::randomlyFindSubstitute(std::list<ShoppingItem>::iterator medicineOnListIt) {
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 generator(seed);
	std::bernoulli_distribution distribution(supportedClientPtr->getProbabilityOfActions());
	bool findSubs = distribution(generator);
	if (findSubs) {
		this->remainingTime++;
		std::shared_ptr<Medicine> substitutePtr = pharmacyIneventory.findSubstitute(medicineOnListIt->getMedicinePtr());
		if (substitutePtr == nullptr) {
			//logger - nie znaleziono zamiennika
            (*logger).operator<<(Messages::failedToFindSubstitute(*medicineOnListIt))<<std::endl;
        } else {
			unsigned idOfOldMedicine = medicineOnListIt->getMedicinePtr()->getId();
			supportedClientPtr->replaceMedicineOnList(medicineOnListIt->getMedicinePtr(), substitutePtr);
            medicineOnListIt->setMedicinePtr(substitutePtr);
			//logger - znaleziono zamiennik
            (*logger).operator<<(Messages::foundSubstitute(idOfOldMedicine,medicineOnListIt->getMedicinePtr()->getId()))<<std::endl;
        }
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
	//logger - zako�czono transakcj�
    if(remainingTime==0){
    (*logger).operator<<(Messages::finishedTransaction(supportedClientPtr,currentCounterPtr->getId()))<<std::endl;}
    else{
        (*logger).operator<<(Messages::finishedTransactionOnEnd(supportedClientPtr, currentCounterPtr->getId()))<<std::endl;
    }
}
