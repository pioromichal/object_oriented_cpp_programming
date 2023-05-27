#include "../include/clients_queue.h"
#include "../include/exceptions.h"

ClientsQueue::ClientsQueue() : clientsPtrsQueue(std::queue<std::unique_ptr<Client>> {}) {}

void ClientsQueue::pushBusinessClient(std::string name, std::string surname, ShoppingList& shoppingList, float probabilityOfActions) {
	clientsPtrsQueue.push(std::make_unique<BusinessClient>(name, surname, shoppingList, probabilityOfActions));
}

void ClientsQueue::pushIndividualClient(std::string name, std::string surname, ShoppingList& shoppingList, float probabilityOfActions) {
	clientsPtrsQueue.push(std::make_unique<IndividualClient>(name, surname, shoppingList, probabilityOfActions));
}

std::unique_ptr<Client> ClientsQueue::popClient() {
    if (clientsPtrsQueue.empty()) {
        throw Exceptions::ClientsQueueIsAlreadyEmpty();
    }
    std::unique_ptr<Client> clientPtr = std::move(clientsPtrsQueue.front());
    clientsPtrsQueue.pop();
    return clientPtr;
}

bool ClientsQueue::isEmpty() const {
    return clientsPtrsQueue.empty();
}

unsigned ClientsQueue::getLength() const {
    return clientsPtrsQueue.size();
}

const std::queue<std::unique_ptr<Client>>& ClientsQueue::getClientsPtrsQueue() const {
    return clientsPtrsQueue;
}