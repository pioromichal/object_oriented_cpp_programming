#include "../include/exceptions.h"

Exceptions::ProbabilityOutOfRange::ProbabilityOutOfRange(const float probability) : std::invalid_argument("Given probability () is out of range [0; 1]") {}

Exceptions::MedicineDoesntExistOnList::MedicineDoesntExistOnList(const std::string nameOfMedicine) : std::invalid_argument("Medcine " + nameOfMedicine + " doesn't exist on the shopping list") {}

Exceptions::ClientsQueueIsAlreadyEmpty::ClientsQueueIsAlreadyEmpty() : std::out_of_range("Queue is already empty, so you cannot pop a Client") {}

Exceptions::SimulationFinishedEarlier::SimulationFinishedEarlier() : std::exception("Simulation has been finished earlier because of lack of clients in queue") {}
