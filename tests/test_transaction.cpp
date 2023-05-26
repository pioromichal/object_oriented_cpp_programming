#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "../include/transaction.h"
#include "../include/medicine.h"
#include "../include/capsules.h"
#include "../include/drops.h"
#include "../include/ointment.h"
#include "../include/powders.h"
#include "../include/syrup.h"
#include "../include/tablets.h"
#include "../include/business_client.h"
#include "../include/individual_client.h"

TEST_CASE("transaction simple tests", "[transaction]") {
    Inventory ZikoInventory;
    Medicine::resetMedId();
    CHECK(ZikoInventory.numberOfMedicines() == 0);
    std::shared_ptr<Medicine> ptr1 = std::make_unique<Capsules>("Capsules1", Affliction::Ache, ActiveSubstance::Aspirin, 200, Price(16, 99), 100, 30);
    ZikoInventory.addNewMedicine(ptr1);
    std::shared_ptr<Medicine> ptr2 = std::make_unique<Drops>("Drops1", Affliction::Pain, ActiveSubstance::Metformin, 1000, Price(23, 00), 100, 100);
    ZikoInventory.addNewMedicine(ptr2);
    std::shared_ptr<Medicine> ptr3 = std::make_unique<Syrup>("Syrup1", Affliction::Pain, ActiveSubstance::Sertraline, 500, Price(80, 00), 100, 500);
    ZikoInventory.addNewMedicine(ptr3);
    std::shared_ptr<Medicine> ptr4 = std::make_unique<Tablets>("Tablets1", Affliction::Ache, ActiveSubstance::Sertraline, 560, Price(27, 55), 100, 50);
    ZikoInventory.addNewMedicine(ptr4);
    std::shared_ptr<Medicine> ptr5 = std::make_unique<Tablets>("Tablets2", Affliction::Rash, ActiveSubstance::Omeprazole, 300, Price(18, 60), 3, 30);
    ZikoInventory.addNewMedicine(ptr5);
    std::shared_ptr<Medicine> ptr6 = std::make_unique<Ointment>("No in magazine", Affliction::Allergy, ActiveSubstance::Metamizole, 200, Price(30, 50), 0, 500);
    ZikoInventory.addNewMedicine(ptr6);
    Counter::resetIdNumbering();

    std::unique_ptr<Counter>  counter1 = std::make_unique<Counter>(true);
    std::unique_ptr<Counter>  counter2 = std::make_unique<Counter>(true);

    SECTION("testing transaction without finding subtitutes") {
        ShoppingList JansList;
        JansList.addMedicineToList(ptr1, 3);
        JansList.addMedicineToList(ptr2, 2);
        JansList.addMedicineToList(ptr3, 4);
        JansList.addMedicineToList(ptr4, 1);

        std::unique_ptr<Client> Jan = std::make_unique<IndividualClient>("Jan", "Kowalski", JansList, 0);

        CHECK_FALSE(counter1->isOccupied());

        std::unique_ptr<Transaction> JansTransaction = std::make_unique<Transaction>(ZikoInventory, std::move(Jan), counter1);
        
        CHECK(counter1->isOccupied());
        CHECK(JansTransaction->getNettoPrice() == Price(474, 86));
        CHECK(JansTransaction->getBruttoPrice() == Price(584, 7));
        CHECK(JansTransaction->getTaxPrice() == Price(109, 21));
        CHECK(ZikoInventory.howManyInMagazine(ptr1) == 97);
        CHECK(ZikoInventory.howManyInMagazine(ptr2) == 98);
        CHECK(ZikoInventory.howManyInMagazine(ptr3) == 96);
        CHECK(ZikoInventory.howManyInMagazine(ptr4) == 99);
        CHECK(ZikoInventory.howManyInMagazine(ptr5) == 3);
        CHECK(ZikoInventory.howManyInMagazine(ptr6) == 0);

        CHECK(JansTransaction->getRemainingTime() == 2);
        CHECK_FALSE(JansTransaction->isFinished());

        JansTransaction->operator--();

        CHECK_FALSE(JansTransaction->isFinished());
        CHECK(JansTransaction->getRemainingTime() == 1);

        JansTransaction->operator--();

        CHECK(JansTransaction->isFinished());
        CHECK(JansTransaction->getRemainingTime() == 0);

        JansTransaction.reset();

        CHECK_FALSE(counter1->isOccupied());
    }

    SECTION("testing transaction with finding subtitutes") {
        ShoppingList PiotrsList;
        PiotrsList.addMedicineToList(ptr3, 2);
        PiotrsList.addMedicineToList(ptr1, 5);
        
        std::unique_ptr<Client> Piotr = std::make_unique<IndividualClient>("Piotr", "Nowak", PiotrsList, 1);

        CHECK_FALSE(counter2->isOccupied());

        std::unique_ptr<Transaction> PiotrsTransaction = std::make_unique<Transaction>(ZikoInventory, std::move(Piotr), counter2);

        CHECK(counter2->isOccupied());
        CHECK(PiotrsTransaction->getNettoPrice() == Price(139, 75));
        CHECK(PiotrsTransaction->getBruttoPrice() == Price(171, 89));
        CHECK(PiotrsTransaction->getTaxPrice() == Price(32, 14));
        CHECK(ZikoInventory.howManyInMagazine(ptr1) == 95);
        CHECK(ZikoInventory.howManyInMagazine(ptr2) == 98);
        CHECK(ZikoInventory.howManyInMagazine(ptr3) == 100);
        CHECK(ZikoInventory.howManyInMagazine(ptr4) == 100);
        CHECK(ZikoInventory.howManyInMagazine(ptr5) == 3);
        CHECK(ZikoInventory.howManyInMagazine(ptr6) == 0);
        CHECK(PiotrsTransaction->getRemainingTime() == 3);
        CHECK_FALSE(PiotrsTransaction->isFinished());

        PiotrsTransaction->operator--();
        
        CHECK(PiotrsTransaction->getRemainingTime() == 2);
        CHECK_FALSE(PiotrsTransaction->isFinished());

        PiotrsTransaction->operator--();

        CHECK_FALSE(PiotrsTransaction->isFinished());
        CHECK(PiotrsTransaction->getRemainingTime() == 1);

        PiotrsTransaction->operator--();

        CHECK(PiotrsTransaction->isFinished());
        CHECK(PiotrsTransaction->getRemainingTime() == 0);

        PiotrsTransaction.reset();

        CHECK_FALSE(counter2->isOccupied());
    }

    SECTION("testing transaction with lack of wanted medicines") {
        ShoppingList MarcinsList;
        MarcinsList.addMedicineToList(ptr6, 2);
        MarcinsList.addMedicineToList(ptr5, 5);
        std::unique_ptr<Client> Marcin = std::make_unique<BusinessClient>("Marcin", "Nowakowski", MarcinsList, 0);
        
        CHECK_FALSE(counter2->isOccupied());

        std::unique_ptr<Transaction> MarcinsTransaction = std::make_unique<Transaction>(ZikoInventory, std::move(Marcin), counter2);


        CHECK(counter2->isOccupied());
        CHECK(MarcinsTransaction->getNettoPrice() == Price(57, 45));
        CHECK(MarcinsTransaction->getBruttoPrice() == Price(62, 04));
        CHECK(MarcinsTransaction->getTaxPrice() == Price(4, 59));
        CHECK(ZikoInventory.howManyInMagazine(ptr1) == 100);
        CHECK(ZikoInventory.howManyInMagazine(ptr2) == 100);
        CHECK(ZikoInventory.howManyInMagazine(ptr3) == 100);
        CHECK(ZikoInventory.howManyInMagazine(ptr4) == 100);
        CHECK(ZikoInventory.howManyInMagazine(ptr5) == 0);
        CHECK(ZikoInventory.howManyInMagazine(ptr6) == 0);
        CHECK(MarcinsTransaction->getRemainingTime() == 3);
        CHECK_FALSE(MarcinsTransaction->isFinished());

        MarcinsTransaction->operator--();

        CHECK(MarcinsTransaction->getRemainingTime() == 2);
        CHECK_FALSE(MarcinsTransaction->isFinished());

        MarcinsTransaction->operator--();

        CHECK_FALSE(MarcinsTransaction->isFinished());
        CHECK(MarcinsTransaction->getRemainingTime() == 1);

        MarcinsTransaction->operator--();

        CHECK(MarcinsTransaction->isFinished());
        CHECK(MarcinsTransaction->getRemainingTime() == 0);

        MarcinsTransaction.reset();

        CHECK_FALSE(counter2->isOccupied());

    }
}