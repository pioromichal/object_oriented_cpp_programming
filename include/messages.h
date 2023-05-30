//
// Created by damia on 28.05.2023.
//

#ifndef PROI_23L_101_APTEKA_MESSAGES_H
#define PROI_23L_101_APTEKA_MESSAGES_H
#include <string>
#include <memory>
#include "client.h"
class Messages {
private:
    inline static const std::string infoTag = " [Info] ";
    inline static const std::string updateTag = " [Update] ";
    inline static const std::string transactionTag = " [Transaction status] ";
    inline static const std::string finalizationTag = " [Finalize] ";
    inline static const std::string endSimulationTag = " [End] ";

public:
    static std::string noClientsInQueue();
    static std::string newClient(const std::unique_ptr<Client>& client);
    static std::string noMoreOpenCounters(unsigned numOfActiveCounters);
    static std::string clientCameToCounter(unsigned clientID, unsigned CounterId, unsigned lengthOfList);
    static std::string openedCounter(int id);
    static std::string closedCounter(int id, int howLongWorked);
    static std::string changedNumberOfMedicines(ShoppingItem &item, unsigned numberLookedFor);
    static std::string failedToSellMedicine(ShoppingItem &medicine);
    static std::string failedToFindSubstitute(ShoppingItem &shoppingItemFromList);
    static std::string foundSubstitute(unsigned oldMedicineId, unsigned newMedicineId);
    static std::string finishedTransaction(std::unique_ptr<Client> &client, unsigned counterId);
    static std::string finishedTransactionOnEnd(std::unique_ptr<Client> &client, unsigned counterId);
};


#endif //PROI_23L_101_APTEKA_MESSAGES_H
