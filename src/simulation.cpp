#include "../include/simulation.h"
#include "../include/file_manager.h"
#include "../include/exceptions.h"

#include <chrono>
#include <random>
#include <iostream>
#include <sstream>
#include <algorithm>

Simulation::Simulation(int nTurns, int nMedicines, int nCounters, int nOpenedCounters, int nStartingClients,
                       std::string &outputPath, ifstream &firstNames, ifstream &lastNames, ifstream &medicineNames) :
	maxNumOfTurns(nTurns), numberOfTurns(1), logger(outputPath), namesData(FileManager::namesFromFile(firstNames, lastNames)), medicineData(FileManager::medicineNamesFromFile(medicineNames)), pharmacy(nCounters, nOpenedCounters), currentTransactions(std::list<std::unique_ptr<Transaction>> {}) {

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	this -> generator = std::mt19937(seed);
	for (int i = 0; i < nMedicines; i++) {
		addRandomMedicineToInventory();
	}

    for (int i = 0; i < nStartingClients; i++) {
        pushRandomClient();
    }
}

void Simulation::run() {
	Transaction::logger = &logger;
	try {
		for (numberOfTurns; numberOfTurns <= maxNumOfTurns; numberOfTurns++) {
            ++logger;
            this->operator++();
		}
	} 
	catch (const Exceptions::SimulationFinishedEarlier& e) {
		//logger - brak kilent�w do obs�ugi
        logger<<Messages::noClientsInQueue()<<std::endl;
	}
    currentTransactions.clear();
}

Simulation& Simulation::operator++() {
	// 1. Przychodzenie klient�w
	pushNewClients();
	// 2. Przypisywanie do wolnych okienek
	assigneClientsToWindows();
	// 3. Dekrementacja transakcji 
	decrementTransactions();
	// 4. Zwalnianie okienek
	releaseCounters();
	// 5. Inkrementacja okienek
	pharmacy.incrementCounters();
	// 6. Zamykanie oraz otwieranie okienek
	manageCountersOpening();


	return *this;
}

void Simulation::decrementTransactions() {
	for (std::unique_ptr<Transaction>& transactionPtr : currentTransactions) {
		transactionPtr->operator--();
	} 
}

void Simulation::releaseCounters() {
	currentTransactions.erase(remove_if(currentTransactions.begin(), currentTransactions.end(), [](const std::unique_ptr<Transaction>& transaction) { return transaction->isFinished(); }), currentTransactions.end());
}

void Simulation::pushNewClients() {	
	std::geometric_distribution<int> geo_distribution(0.4);
	int newClientsNum = geo_distribution(generator);
	for (int i = 1; i <= newClientsNum; i++) {
		pushRandomClient();
        logger<<Messages::newClient(pharmacy.getNewestClient())<<std::endl;
	}
	//logger - przyszli jacy� klienci
}

void Simulation::assigneClientsToWindows() {
	bool isOpenedCounter = true;
	do {
		try {
			currentTransactions.push_back(std::make_unique<Transaction>(pharmacy.getInventory(), pharmacy.popClient(), pharmacy.getOpenCounter()));
			//logger - klient podszed� do okienka
		}
		catch (const Exceptions::ClientsQueueIsAlreadyEmpty& e) {
			if (currentTransactions.empty()) {
				throw Exceptions::SimulationFinishedEarlier();
			}
			isOpenedCounter = false;
			//logger - koniec klient�w
            logger<<Messages::noClientsInQueue()<<std::endl;
		}
		catch (const std::invalid_argument& e) {
			isOpenedCounter = false;
			//logger - brak wolnych okienek
            logger<< Messages::noMoreOpenCounters(pharmacy.getNumOfCounters())<<std::endl;

		}
	} while (isOpenedCounter);
}

void Simulation::manageCountersOpening() {
	std::bernoulli_distribution bern_action_distribution(1-10.0/(pharmacy.getNumOfCounters() + 9));
	std::uniform_real_distribution<float> uni_distribution(0.0f, 1.0f);
	std::bernoulli_distribution bern_close_distribution(1.0 * pharmacy.getNumOfOpenCounters() / pharmacy.getNumOfCounters());
	if (bern_action_distribution(generator)) {
		if (bern_close_distribution(generator)) {
			std::unique_ptr<Counter>& counterToClose = pharmacy.findLongestWorkingCounter();
			if (!counterToClose->isOccupied()) {
                logger<<Messages::closedCounter(counterToClose->getId(),counterToClose->getTimeOpened())<<std::endl;
				counterToClose->closeCounter();
				//logger - zamkni�to okienko
			}
		} else {
			for (int counterId = 1; counterId <= pharmacy.getNumOfCounters(); counterId++) {
				if (!pharmacy.getCounter(counterId)->isOpened()) {
					pharmacy.openCounter(counterId);
                    logger<<Messages::openedCounter(counterId)<<std::endl;
					//logger - otwarto okienko
					return;
				}
			}
		}
	} 
}

void Simulation::pushRandomClient() {
	std::bernoulli_distribution bern_distribution(0.5);
	std::uniform_real_distribution<float> uni_distribution(0.0f, 1.0f);
	if (bern_distribution(generator)) {
		pharmacy.pushBusinessClient(generateRandomName(), generateRandomSurname(), generateRandomShoppingList(), uni_distribution(generator));
	} else {
		pharmacy.pushIndividualClient(generateRandomName(), generateRandomSurname(), generateRandomShoppingList(), uni_distribution(generator));
	}
}

void Simulation::addRandomMedicineToInventory() {
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

	default:
		medicinePtr = nullptr;
		throw Exceptions::ProbabilityOutOfRange(randomMedicineType,6);

	}
	pharmacy.addMedicineToInventory(medicinePtr);


}

ShoppingList Simulation::generateRandomShoppingList() {
	std::geometric_distribution<int> geo_list_distribution(0.5);
	int shoppingListLength = geo_list_distribution(generator) + 2;
	std::geometric_distribution<int> geo_item_distribution(0.3);
	ShoppingList randomShoppingList;
	for (int i = 1; i <= shoppingListLength; i++) {
		randomShoppingList.addMedicineToList(pharmacy.findRandomMedicine(), geo_item_distribution(generator) + 1);
	}
	return randomShoppingList;
}

std::string& Simulation::generateRandomName() {
	std::uniform_int_distribution<int> uni_distribution(0, namesData.fLength-1);
	return namesData.firstNames.at(uni_distribution(generator));
}

std::string& Simulation::generateRandomSurname() {
	std::uniform_int_distribution<int> uni_distribution(0, namesData.lLength - 1);
	return namesData.lastNames.at(uni_distribution(generator));
}

std::string& Simulation::generateRandomMedicineName() {
	std::uniform_int_distribution<int> uni_distribution(0, medicineData.length - 1);
	return medicineData.medicineNames.at(uni_distribution(generator));
}

Affliction Simulation::generateRandomAffliction() {
	std::uniform_int_distribution<int> uni_distribution(0, static_cast<int>(Affliction::Count) - 1);
	return static_cast<Affliction>(uni_distribution(generator));
}

ActiveSubstance Simulation::generateRandomActiveSubstance()
{
	std::uniform_int_distribution<int> uni_distribution(0, static_cast<int>(ActiveSubstance::Count) - 1);
	return static_cast<ActiveSubstance>(uni_distribution(generator));
}

unsigned Simulation::generateRandomVolume()
{
	std::lognormal_distribution<float> norm_distribution(6, 0.2);
	return static_cast<unsigned>(norm_distribution(generator)) + 1;
}

unsigned Simulation::generateRandomNumber()
{
	std::lognormal_distribution<float> norm_distribution(3, 0.2);
	return static_cast<unsigned>(norm_distribution(generator)) + 1;
}

unsigned Simulation::generateRandomSachets()
{
	std::lognormal_distribution<float> norm_distribution(2.5, 0.2);
	return static_cast<unsigned>(norm_distribution(generator)) + 1;
}

unsigned Simulation::generateRandomAmount()
{
	std::lognormal_distribution<float> norm_distribution(7, 0.4);
	return static_cast<unsigned>(norm_distribution(generator)) + 1;
}

unsigned Simulation::generateRandomMiligrams()
{
	std::lognormal_distribution<float> norm_distribution(7, 0.5);
	return static_cast<unsigned>(norm_distribution(generator)) + 1;
}

Price Simulation::generateRandomPrice()
{
	std::lognormal_distribution<float> zlotys_distribution(3.7, 0.3);
	std::lognormal_distribution<float> grosze_distribution(4, 0.4);
	return Price(static_cast<unsigned>(zlotys_distribution(generator)), static_cast<unsigned>(abs(100 - grosze_distribution(generator))) + 1);
}
