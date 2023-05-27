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
    class ClientsQueueIsAlreadyEmpty : public std::invalid_argument {
    public: ClientsQueueIsAlreadyEmpty();
    };
}
#endif
