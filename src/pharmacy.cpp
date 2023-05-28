#include <random>
#include <chrono>
#include <memory>
#include <stdexcept>
#include "../include/pharmacy.h"
Pharmacy::Pharmacy(int nCounters, int nOpenedCounters) : counters(nCounters,nOpenedCounters) {

}

void Pharmacy::addMedicineToInventory(std::shared_ptr<Medicine> medicine) {
    inventory.addNewMedicine(medicine);
}

Inventory& Pharmacy::getInventory()
{
	return inventory;
}

unsigned Pharmacy::getNumOfCounters() const
{
	return counters.getAllCounters();
}

unsigned Pharmacy::getNumOfOpenCounters() const {
	return counters.getOpenedCounters();
}

std::unique_ptr<Counter>& Pharmacy::getCounter(unsigned id) {
	return counters.getCounter(id);
}

std::unique_ptr<Counter>& Pharmacy::findLongestWorkingCounter() {
	return counters.findLongestWorking();
}

void Pharmacy::openCounter(unsigned id) {
	counters.openCounter(id);
}

void Pharmacy::incrementCounters() {
	counters.nextTurn();
}

void Pharmacy::pushBusinessClient(std::string name, std::string surname, ShoppingList& shoppingList, float probabilityOfActions) {
	queue.pushBusinessClient(name, surname, shoppingList, probabilityOfActions);
}

void Pharmacy::pushIndividualClient(std::string name, std::string surname, ShoppingList& shoppingList, float probabilityOfActions) {
	queue.pushIndividualClient(name, surname, shoppingList, probabilityOfActions);
}

std::shared_ptr<Medicine> Pharmacy::findRandomMedicine() {
	return inventory.findRandomMedicine();
}

CountersList& Pharmacy::getCountersList() {
	return counters;
}

std::unique_ptr<Counter>& Pharmacy::getOpenCounter()
{
	return counters.getOpenCounter();
}

std::unique_ptr<Client> Pharmacy::popClient() {
	return queue.popClient();
}
