#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "../include/clients_queue.h"
#include "../include/client.h"
#include "../include/business_client.h"
#include "../include/individual_client.h"
#include "../include/capsules.h"
#include "../include/tablets.h"

TEST_CASE("simple clients queue tests") {
	Client::resetClientId();
	std::shared_ptr<Medicine> Capsules1 = std::make_shared<Capsules>("Capsules1", Affliction::Ache, ActiveSubstance::Aspirin, 200, Price(16, 99), 100, 30);
	std::shared_ptr<Medicine> Tablets1 = std::make_shared<Tablets>("Tablets1", Affliction::Allergy, ActiveSubstance::Sertraline, 560, Price(27, 55), 100, 50);

	ShoppingList JansList;
	JansList.addMedicineToList(Capsules1, 3);
	JansList.addMedicineToList(Tablets1, 1);
	ShoppingList PiotrsList;
	PiotrsList.addMedicineToList(Tablets1, 4);
	PiotrsList.addMedicineToList(Capsules1, 2);
	ShoppingList MarcinsList;
	MarcinsList.addMedicineToList(Tablets1, 1);

	ClientsQueue ZikoQueue;
	CHECK(ZikoQueue.isEmpty());
	CHECK(ZikoQueue.getLength() == 0);
	CHECK(ZikoQueue.getClientsPtrsQueue() == std::queue<std::unique_ptr<Client>> {});

	ZikoQueue.pushBusinessClient("Piotr", "Nowak", PiotrsList, 0.345);
	CHECK_FALSE(ZikoQueue.isEmpty());
	CHECK(ZikoQueue.getLength() == 1);
	CHECK(ZikoQueue.getClientsPtrsQueue().front()->getId() == 1);
	CHECK(ZikoQueue.getClientsPtrsQueue().back()->getId() == 1);

	ZikoQueue.pushIndividualClient("Jan", "Kowalski", JansList, 0.789);
	CHECK_FALSE(ZikoQueue.isEmpty());
	CHECK(ZikoQueue.getLength() == 2);
	CHECK(ZikoQueue.getClientsPtrsQueue().front()->getId() == 1);
	CHECK(ZikoQueue.getClientsPtrsQueue().back()->getId() == 2);

	ZikoQueue.pushIndividualClient("Marcin", "Nowak", MarcinsList, 0.895);
	CHECK_FALSE(ZikoQueue.isEmpty());
	CHECK(ZikoQueue.getLength() == 3);
	CHECK(ZikoQueue.getClientsPtrsQueue().front()->getId() == 1);
	CHECK(ZikoQueue.getClientsPtrsQueue().back()->getId() == 3);

	CHECK(ZikoQueue.popClient()->getId() == 1);
	CHECK_FALSE(ZikoQueue.isEmpty());
	CHECK(ZikoQueue.getLength() == 2);
	CHECK(ZikoQueue.getClientsPtrsQueue().front()->getId() == 2);
	CHECK(ZikoQueue.getClientsPtrsQueue().back()->getId() == 3);

	CHECK(ZikoQueue.popClient()->getId() == 2);
	CHECK_FALSE(ZikoQueue.isEmpty());
	CHECK(ZikoQueue.getLength() == 1);
	CHECK(ZikoQueue.getClientsPtrsQueue().front()->getId() == 3);
	CHECK(ZikoQueue.getClientsPtrsQueue().back()->getId() == 3);

	CHECK(ZikoQueue.popClient()->getId() == 3);
	CHECK(ZikoQueue.isEmpty());
	CHECK(ZikoQueue.getLength() == 0);
	CHECK(ZikoQueue.getClientsPtrsQueue() == std::queue<std::unique_ptr<Client>> {});

}