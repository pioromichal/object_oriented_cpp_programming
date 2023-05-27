#include "../include/simulation.h"
#include "../include/file_manager.h"
#include "../include/exceptions.h"

#include <chrono>
#include <random>
#include <iostream>
#include <sstream>

Simulation::Simulation(int nTurns, int nMedicines, int nCounters, int nOpenedCounters, int nStartingClients,
                       ifstream &firstNames,
                       ifstream &lastNames, ifstream &medicineNames) : numberOfTurns(nTurns), namesData(
        FileManager::namesFromFile(firstNames, lastNames)),
                                                                       medicineData(FileManager::medicineNamesFromFile(
                                                                               medicineNames)),
                                                                       pharmacy(nCounters, nOpenedCounters) {

    for (int i = 0; i < nStartingClients; i++) {
        //TODO function generating data from namesData
        pharmacy.pushNewClient(randomName(), randomSurname());
    }

    for (int i = 0; i < nMedicines; i++) {
        //TODO function generating data from medicineData
        pharmacy.addRandomMedicine(randomMedicineName());
    }
}

std::string &Simulation::randomName() {
    return (std::string &) "Place";
}

std::string &Simulation::randomSurname() {
    return (std::string &) "holder";
}


void Simulation::simulate() {
	for (numberOfTurns; numberOfTurns < maksNumOfTurns; numberOfTurns++) {
		this->operator++();
	}
}

Simulation& Simulation::operator++() {
	// 1. Przychodzenie klientów
	pushNewClients();
	// 2. Przypisywanie do wolnych okienek
	assigneClientsToWindows();
	// 3. Dekrementacja transakcji i zwalnianie okienek
	decrementTransactionsAndReleaseCounters();
	// 4. Inkrementacja okienek
	pharmacy.incrementCounters();
	// 5. Zamykanie oraz otwieranie okienek
	manageCountersOpening();
	return *this;
}

void Simulation::decrementTransactionsAndReleaseCounters() {
	for (std::list<std::unique_ptr<Transaction>>::iterator transactionIt = currentTransactions.begin(); transactionIt != currentTransactions.end(); ) {
		if ((*transactionIt)->isFinished()) {
			transactionIt == currentTransactions.erase(transactionIt);
			//ewentualnie tu mo¿na daæ koniec transakcji zamiast wewn¹trz destruktora
		}
		else {
			(*transactionIt)->operator--();
			transactionIt++;
		}
	}
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
			//coœ z zakoñczeniem symulacji
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

std::string Simulation::generateRandomName() {
	/*unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 generator(seed);
	std::uniform_real_distribution<int> uni_distribution(0, namesData.fLength-1);
	return namesData.firstNames.at(uni_distribution(generator));*/
	return "Name";
}

std::string Simulation::generateRandomSurname() {
	/*unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 generator(seed);
	std::uniform_real_distribution<int> uni_distribution(0, namesData.lLength - 1);
	return namesData.lastNames.at(uni_distribution(generator));*/
	return "Surname";
}
std::string &Simulation::randomMedicineName() {
    return (std::string &) "Hatered";
}
