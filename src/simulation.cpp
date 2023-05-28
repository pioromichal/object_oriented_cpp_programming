#include "../include/simulation.h"
#include "../include/file_manager.h"
#include "../include/exceptions.h"

#include <chrono>
#include <random>
#include <iostream>
#include <sstream>
#include <algorithm>

Simulation::Simulation(int nTurns, int nMedicines, int nCounters, int nOpenedCounters, int nStartingClients, ifstream &firstNames, ifstream &lastNames, ifstream &medicineNames) : 
	maxNumOfTurns(nTurns), numberOfTurns(0), namesData(FileManager::namesFromFile(firstNames, lastNames)), medicineData(FileManager::medicineNamesFromFile(medicineNames)), pharmacy(nCounters, nOpenedCounters), currentTransactions(std::list<std::unique_ptr<Transaction>> {}) {

	for (int i = 0; i < nMedicines; i++) {
		//TODO function generating data from medicineData
		addRandomMedicineToInventory();
	}

    for (int i = 0; i < nStartingClients; i++) {
		pushRandomClient();
    }
}

void Simulation::run() {
	for (numberOfTurns; numberOfTurns < maxNumOfTurns; numberOfTurns++) {
		this->operator++();
	}
}

Simulation& Simulation::operator++() {
	// 1. Przychodzenie klientów
	pushNewClients();
	// 2. Przypisywanie do wolnych okienek
	assigneClientsToWindows();
	// 3. Dekrementacja transakcji i zwalnianie okienek
	decrementTransactions();
	releaseCounters();
	// 4. Inkrementacja okienek
	pharmacy.incrementCounters();
	// 5. Zamykanie oraz otwieranie okienek
	manageCountersOpening();
	return *this;
}

void Simulation::decrementTransactions() {
	for (std::unique_ptr<Transaction>& transactionPtr : currentTransactions) {
		transactionPtr->operator--();
	}
}

void Simulation::releaseCounters() {
	
	bool wasFinshedTransaction = true;

	do {
		auto transactionIt = remove_if(currentTransactions.begin(), currentTransactions.end(), [](const std::unique_ptr<Transaction>& transaction) { return transaction->isFinished(); });
		if (transactionIt == currentTransactions.end()) {
			currentTransactions.erase(transactionIt);
			wasFinshedTransaction = true;
		}
		else {
			wasFinshedTransaction = false;
		}

	} while (wasFinshedTransaction);
}

void Simulation::pushNewClients() {
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 generator(seed);
	std::geometric_distribution<int> geo_distribution(0.7);
	int newClientsNum = geo_distribution(generator);
	for (int i = 1; i <= newClientsNum; i++) {
		pushRandomClient();
	}
	//logger - przyszli jacyœ klienci
}

void Simulation::assigneClientsToWindows() {
	bool isOpenedCounter = true;
	do {
		try {
			std::unique_ptr<Counter>& openedCounter = pharmacy.getOpenCounter();
			currentTransactions.push_back(std::make_unique<Transaction>(pharmacy.getInventory(), pharmacy.popClient(), openedCounter));
			//logger - klient podszed³ do okienka
		}
		catch (const Exceptions::ClientsQueueIsAlreadyEmpty& e) {
			isOpenedCounter = false;
			//logger - koniec klientów
			//TODO coœ z zakoñczeniem symulacji
		}
		catch (const std::invalid_argument& e) {
			isOpenedCounter = false;
			//logger - brak wolnych okienek
		}
	} while (isOpenedCounter);
}

void Simulation::manageCountersOpening() {
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 generator(seed);
	std::bernoulli_distribution bern_action_distribution(1-10.0/(pharmacy.getNumOfCounters() + 9));
	std::uniform_real_distribution<float> uni_distribution(0.0f, 1.0f);
	std::bernoulli_distribution bern_close_distribution(1.0 * pharmacy.getNumOfOpenCounters() / pharmacy.getNumOfCounters());
	if (bern_action_distribution(generator)) {
		if (bern_close_distribution(generator)) {
			std::unique_ptr<Counter>& counterToClose = pharmacy.findLongestWorkingCounter();
			if (!counterToClose->isOccupied()) {
				counterToClose->closeCounter();
				//logger - zamkniêto okienko
			}
		} else {
			for (int counterId = 1; counterId <= pharmacy.getNumOfCounters(); counterId++) {
				if (!pharmacy.getCounter(counterId)->isOpened()) {
					pharmacy.openCounter(counterId);
					//logger - otwarto okienko
					return;
				}
			}
		}
	} 
}

void Simulation::pushRandomClient() {
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 generator(seed);
	std::bernoulli_distribution bern_distribution(0.5);
	std::uniform_real_distribution<float> uni_distribution(0.0f, 1.0f);
	if (bern_distribution(generator)) {
		pharmacy.pushBusinessClient(generateRandomName(), generateRandomSurname(), generateRandomShoppingList(), uni_distribution(generator));
	} else {
		pharmacy.pushIndividualClient(generateRandomName(), generateRandomSurname(), generateRandomShoppingList(), uni_distribution(generator));
	}
}

void Simulation::addRandomMedicineToInventory() {
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 generator(seed);
	std::uniform_int_distribution<int> uni_distribution(1, 6);
	int randomMedicineType = uni_distribution(generator);
	std::shared_ptr<Medicine> medicinePtr;
	switch (randomMedicineType) {
	case 1:
		//Capsules
		medicinePtr = std::make_shared<Capsules>(generateRandomMedicineName(), generateRandomAffliction(), generateRandomActiveSubstance(), generateRandomMiligrams(), generateRandomPrice(), generateRandomAmount(), generateRandomNumber());
		break;
	case 2:
		//Drops
		medicinePtr = std::make_shared<Drops>(generateRandomMedicineName(), generateRandomAffliction(), generateRandomActiveSubstance(), generateRandomMiligrams(), generateRandomPrice(), generateRandomAmount(), generateRandomVolume());
		break;
	case 3:
		//Ointment
		medicinePtr = std::make_shared<Ointment>(generateRandomMedicineName(), generateRandomAffliction(), generateRandomActiveSubstance(), generateRandomMiligrams(), generateRandomPrice(), generateRandomAmount(), generateRandomVolume());
		break;
	case 4:
		//Powders
		medicinePtr = std::make_shared<Powders>(generateRandomMedicineName(), generateRandomAffliction(), generateRandomActiveSubstance(), generateRandomMiligrams(), generateRandomPrice(), generateRandomAmount(), generateRandomSachets());
		break;
	case 5:
		//Syrup
		medicinePtr = std::make_shared<Syrup>(generateRandomMedicineName(), generateRandomAffliction(), generateRandomActiveSubstance(), generateRandomMiligrams(), generateRandomPrice(), generateRandomAmount(), generateRandomVolume());
		break;
	case 6:
		//Tablets
		medicinePtr = std::make_shared<Tablets>(generateRandomMedicineName(), generateRandomAffliction(), generateRandomActiveSubstance(), generateRandomMiligrams(), generateRandomPrice(), generateRandomAmount(), generateRandomNumber());
		break;
		//TODO throw some fancy exception
	default:
		medicinePtr = nullptr;
		throw std::invalid_argument("Something went wrong here");

	}
	pharmacy.addMedicineToInventory(medicinePtr);


}

ShoppingList Simulation::generateRandomShoppingList() {
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 generator(seed);
	std::geometric_distribution<int> geo_list_distribution(0.5);
	int shoppingListLength = geo_list_distribution(generator) + 1;
	std::geometric_distribution<int> geo_item_distribution(0.3);
	ShoppingList randomShoppingList;
	for (int i = 1; i <= shoppingListLength; i++) {
		randomShoppingList.addMedicineToList(pharmacy.findRandomMedicine(), geo_item_distribution(generator) + 1);
	}
	return randomShoppingList;
}

std::string& Simulation::generateRandomName() {
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 generator(seed);
	std::uniform_int_distribution<int> uni_distribution(0, namesData.fLength-1);
	return namesData.firstNames.at(uni_distribution(generator));
}

std::string& Simulation::generateRandomSurname() {
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 generator(seed);
	std::uniform_int_distribution<int> uni_distribution(0, namesData.lLength - 1);
	return namesData.lastNames.at(uni_distribution(generator));
}

std::string& Simulation::generateRandomMedicineName() {
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 generator(seed);
	std::uniform_int_distribution<int> uni_distribution(0, medicineData.length - 1);
	return medicineData.medicineNames.at(uni_distribution(generator));
}

Affliction Simulation::generateRandomAffliction() {
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 generator(seed);
	std::uniform_int_distribution<int> uni_distribution(0, static_cast<int>(Affliction::Count) - 1);
	return static_cast<Affliction>(uni_distribution(generator));
}

ActiveSubstance Simulation::generateRandomActiveSubstance()
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 generator(seed);
	std::uniform_int_distribution<int> uni_distribution(0, static_cast<int>(ActiveSubstance::Count) - 1);
	return static_cast<ActiveSubstance>(uni_distribution(generator));
}

unsigned Simulation::generateRandomVolume()
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 generator(seed);
	std::lognormal_distribution<float> norm_distribution(6, 0.2);
	return static_cast<unsigned>(norm_distribution(generator)) + 1;
}

unsigned Simulation::generateRandomNumber()
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 generator(seed);
	std::lognormal_distribution<float> norm_distribution(3, 0.2);
	return static_cast<unsigned>(norm_distribution(generator)) + 1;
}

unsigned Simulation::generateRandomSachets()
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 generator(seed);
	std::lognormal_distribution<float> norm_distribution(2.5, 0.2);
	return static_cast<unsigned>(norm_distribution(generator)) + 1;
}

unsigned Simulation::generateRandomAmount()
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 generator(seed);
	std::lognormal_distribution<float> norm_distribution(7, 0.4);
	return static_cast<unsigned>(norm_distribution(generator)) + 1;
}

unsigned Simulation::generateRandomMiligrams()
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 generator(seed);
	std::lognormal_distribution<float> norm_distribution(7, 0.5);
	return static_cast<unsigned>(norm_distribution(generator)) + 1;
}

Price Simulation::generateRandomPrice()
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 generator(seed);
	std::lognormal_distribution<float> zlotys_distribution(4.5, 0.5);
	std::lognormal_distribution<float> grosze_distribution(4, 0.4);
	return Price(static_cast<unsigned>(zlotys_distribution(generator)), static_cast<unsigned>(grosze_distribution(generator)) + 1);
}
