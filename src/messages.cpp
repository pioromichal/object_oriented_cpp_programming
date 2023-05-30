#include "../include/messages.h"
#include <sstream>


std::string Messages::noClientsInQueue() {
    std::string message = infoTag+"There are no more clients waiting in the queue";
    return message;
}

std::string Messages::newClient(const std::unique_ptr<Client> &client) {
    unsigned clientID = client->getId();
    unsigned clientLength = client->getMedicinesList().size();
    std::string message =updateTag+"New client "+std::to_string(clientID)+" with "+std::to_string(clientLength)+" items on the list came to the pharmacy.";
    return message;
}

std::string Messages::noMoreOpenCounters(unsigned numOfActiveCounters) {
    std::string message = infoTag+"All " +std::to_string(numOfActiveCounters)+" counters are currently busy.";
    return message;
}

std::string Messages::clientCameToCounter(unsigned clientID, unsigned CounterId, unsigned lengthOfList) {
    std::string message = updateTag+"Client "+std::to_string(clientID)+" walked to the counter "+std::to_string(CounterId)+" with "+std::to_string(lengthOfList)+" items on the list.";
    return message;
}

std::string Messages::openedCounter(int id) {
    std::string message = updateTag +"New counter with id "+std::to_string(id)+"has been opened.";
    return message;
}

std::string Messages::closedCounter(int id, int howLongWorked) {
    std::string message = updateTag+"Counter with id"+std::to_string(id)+" has been closed after working for"+std::to_string(howLongWorked)+" turns.";
    return message;
}

std::string Messages::changedNumberOfMedicines(ShoppingItem &item, unsigned numberLookedFor) {
    unsigned medicineId = item.getMedicinePtr()->getId();
    unsigned diff = numberLookedFor-item.getMedicinePtr()->getAmountInPharmacy();
    std::string message = transactionTag + "There is not "+std::to_string(numberLookedFor) +" units of medicine "+
            std::to_string(medicineId)+", so " + std::to_string(item.getMedicinePtr()->getAmountInPharmacy())+" has been sold and the remaining "+
            std::to_string(diff)+" has been swapped.";
    return message;
}

std::string Messages::failedToSellMedicine(ShoppingItem &medicine) {
    std::string message = transactionTag+"Medicine "+ std::to_string(medicine.getMedicinePtr()->getId())+" could not be sold at all";
    return message;
}

std::string Messages::failedToFindSubstitute(ShoppingItem &shoppingItemFromList) {
    std::string message = transactionTag+"After lengthy searches, the substitute for medicine with id "+ std::to_string(shoppingItemFromList.getMedicinePtr()->getId())+" could not be found.";
    return message;
}

std::string Messages::foundSubstitute(unsigned oldMedicineId, unsigned newMedicineId) {
    std::string message = transactionTag+"After lengthy searches, the substitute for medicine with id "+ std::to_string(oldMedicineId)+" has been changed for a medicine with id "+
            std::to_string(newMedicineId);
    return message;
}

std::string Messages::finishedTransaction(std::unique_ptr<Client> &client, unsigned counterId) {
    std::ostringstream ss;
    ss<<"Client "<<client->getId()<<" has finished his transaction and bought "<< client->getMedicinesList().size()<<" different medicines, paying in total "<< client->calculateBruttoPrice();
    std::string message = finalizationTag+ss.str();
    return message;
}

std::string Messages::finishedTransactionOnEnd(std::unique_ptr<Client>& client, unsigned counterId)
{
    std::ostringstream ss;
    ss << "Client " << client->getId() << " has finished his transaction earlier, due to end of simulation, and bought " << client->getMedicinesList().size() << " different medicines, paying in total " << client->calculateBruttoPrice();
    std::string message = endSimulationTag + ss.str();
    return message;
}

std::string Messages::sumUpSimulation(Price price, int clients) {
    std::ostringstream  ss;
    ss<<endSimulationTag<<"After long day of work pharmacy closes after serving "<< clients<<" who bought goods for "<<price;
    return ss.str();
}

std::string Messages::simulationBegins(int counter, int openedCounter, int nClients) {
    std::ostringstream ss;
    ss<<"Pharmacy opens its doors with "<<openedCounter<<" counters working out of "<<counter<<", "<<nClients<<" clients are already waiting outside";
    return ss.str();
}
