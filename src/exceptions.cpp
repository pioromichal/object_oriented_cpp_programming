#include "../include/exceptions.h"

Exceptions::ProbabilityOutOfRange::ProbabilityOutOfRange(const float probability) : std::invalid_argument("Given probability () is out of range [0; 1]") {}

Exceptions::ProbabilityOutOfRange::ProbabilityOutOfRange(int ans, int max):std::invalid_argument("Somehow the value"+std::to_string(ans)+" exceeded accepted range"+std::to_string(max)) {

}

Exceptions::MedicineDoesntExistOnList::MedicineDoesntExistOnList(const std::string nameOfMedicine) : std::invalid_argument("Medcine " + nameOfMedicine + " doesn't exist on the shopping list") {}

Exceptions::ClientsQueueIsAlreadyEmpty::ClientsQueueIsAlreadyEmpty() : std::out_of_range("Queue is already empty, so you cannot pop a Client") {}

Exceptions::SimulationFinishedEarlier::SimulationFinishedEarlier() : std::out_of_range("Simulation has been finished due to lack of clients in pharmacy") {}

Exceptions::TransactionGotWrongCounter::TransactionGotWrongCounter() : std::invalid_argument("Given counter to the transacton is closed or occupied") {}

Exceptions::WrongJSONPath::WrongJSONPath(std::string &path): std::invalid_argument("Given path:"+path+"is incorrect and file could not be opened.") {
}

Exceptions::IncorrectDataFromJSON::IncorrectDataFromJSON() : std::invalid_argument("Some data passed by JSON file are incorrect"){
}
