#include "../include/exceptions.h"

Exceptions::ProbabilityOutOfRange::ProbabilityOutOfRange(const float probability) : std::invalid_argument("Given probability () is out of range [0; 1]") {}

Exceptions::MedicineDoesntExistOnList::MedicineDoesntExistOnList(const std::string nameOfMedicine) : std::invalid_argument("Medcine " + nameOfMedicine + " doesn't exist on the shopping list") {}

Exceptions::ClientsQueueIsAlreadyEmpty::ClientsQueueIsAlreadyEmpty() : std::invalid_argument("Queue is already empty, so you cannot pop a Client") {}
