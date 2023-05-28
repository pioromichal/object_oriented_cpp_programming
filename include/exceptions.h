#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>

namespace Exceptions {
    class ProbabilityOutOfRange : public std::invalid_argument {
    public: ProbabilityOutOfRange(const float probability);
    };
    class MedicineDoesntExistOnList : public std::invalid_argument {
    public: MedicineDoesntExistOnList(const std::string nameOfMedicine);
    };
    class ClientsQueueIsAlreadyEmpty : public std::out_of_range {
    public: ClientsQueueIsAlreadyEmpty();
    };
    class SimulationFinishedEarlier : public std::exception {
    public: SimulationFinishedEarlier();
    };
}
#endif
