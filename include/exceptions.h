#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>

namespace Exceptions {
    class ProbabilityOutOfRange : public std::invalid_argument {
    public: ProbabilityOutOfRange(const float probability);
        ProbabilityOutOfRange(int ans,int max);
    };
    class MedicineDoesntExistOnList : public std::invalid_argument {
    public: MedicineDoesntExistOnList(const std::string nameOfMedicine);
    };
    class ClientsQueueIsAlreadyEmpty : public std::out_of_range {
    public: ClientsQueueIsAlreadyEmpty();
    };
    class SimulationFinishedEarlier : public std::out_of_range {
    public: SimulationFinishedEarlier();
    };
    class TransactionGotWrongCounter : public std::invalid_argument {
    public: TransactionGotWrongCounter();
    };
    class WrongJSONPath : public std::invalid_argument{
    public: WrongJSONPath(std::string &path);
    };
class IncorrectDataFromJSON: public std::invalid_argument{
public: IncorrectDataFromJSON();
};

}
#endif
