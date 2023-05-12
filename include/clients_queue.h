#ifndef PROI_23L_101_APTEKA_CLIENTS_QUEUE_H
#define PROI_23L_101_APTEKA_CLIENTS_QUEUE_H

#include "client.h"
#include "business_client.h"
#include "individual_client.h"
#include <memory>
#include <queue>

class ClientsQueue {
	private:
		std::queue<std::unique_ptr<Client>> clientsPtrsQueue;
	public:
		ClientsQueue();
		void pushBusinessClient(std::string name, std::string surname, ShoppingList& shoppingList, float probabilityOfActions);
		void pushIndividualClient(std::string name, std::string surname, ShoppingList& shoppingList, float probabilityOfActions);
		std::unique_ptr<Client> popClient();
		bool isEmpty();
		unsigned getLength();
		const std::queue<std::unique_ptr<Client>>& getClientsPtrsQueue() const;
};


#endif //PROI_23L_101_APTEKA_CLIENTS_QUEUE_H
