#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include <memory>
#include "../include/inventory.h"
#include "../include/medicine.h"
#include "../include/capsules.h"
#include "../include/drops.h"
#include "../include/ointment.h"
#include "../include/powders.h"
#include "../include/syrup.h"
#include "../include/tablets.h"

TEST_CASE("Test Inventory"){
    Inventory inventory;
    Medicine::resetMedId();
    REQUIRE(inventory.numberOfMedicines()==0);
    std::shared_ptr<Medicine> ptr1 = std::make_unique<Capsules>("Capsules1", Affliction::Ache, ActiveSubstance::Aspirin, 200, Price(16, 99), 100, 30);
    inventory.addNewMedicine(ptr1);
    std::shared_ptr<Medicine> ptr2 = std::make_unique<Drops>("Drops1", Affliction::Pain, ActiveSubstance::Metformin, 1000, Price(23, 00), 100, 100);
    inventory.addNewMedicine(ptr2);
    std::shared_ptr<Medicine> ptr3 = std::make_unique<Syrup>("Syrup1", Affliction::Pain, ActiveSubstance::Sertraline, 500, Price(80, 00), 100, 500);
    inventory.addNewMedicine(ptr3);
    std::shared_ptr<Medicine> ptr4 = std::make_unique<Tablets>("Tablets1", Affliction::Ache, ActiveSubstance::Sertraline, 560, Price(27, 55), 100, 50);
    inventory.addNewMedicine(ptr4);
    std::shared_ptr<Medicine> ptr5 = std::make_unique<Tablets>("Tablets2", Affliction::Rash, ActiveSubstance::Omeprazole, 300, Price(18, 60), 1, 30);
    inventory.addNewMedicine(ptr5);
    std::shared_ptr<Medicine> ptr6 = std::make_unique<Ointment>("No in magazine", Affliction::Allergy, ActiveSubstance::Metamizole, 200, Price(30, 50), 0, 500);
    inventory.addNewMedicine(ptr6);
    SECTION("Testing basic properties of inventory"){
        CHECK(inventory.numberOfMedicines()==6);
        CHECK(inventory.numberOfMedicines(Affliction::Rash)==1);
        CHECK(inventory.numberOfMedicines(Affliction::Pain)==2);
        CHECK(inventory.numberOfMedicines(Affliction::Ache)==2);
        CHECK(inventory.numberOfMedicines(Affliction::Poisoning)==0);
    }SECTION("Decreasing and isInMagazine"){
        CHECK(inventory.isMedicineInMagazine(ptr1));
        CHECK(inventory.isMedicineInMagazine(ptr2));
        CHECK_FALSE(inventory.isMedicineInMagazine(ptr6));
        inventory.pickMedicine(ptr5);
        CHECK_FALSE(inventory.isMedicineInMagazine(ptr5));
        inventory.pickMedicine(ptr1);
        CHECK(ptr1->getAmountInPharmacy()==99);
        inventory.pickMedicine(ptr1);
        CHECK(ptr1->getAmountInPharmacy()==98);
        inventory.pickMedicine(ptr5);
        CHECK_FALSE(inventory.isMedicineInMagazine(ptr5));
    }SECTION("Finding random medicine and substitute"){
        auto substitute = inventory.findSubstitute(ptr3);
        CHECK(substitute->getName()=="Drops1");
        CHECK(substitute->getAfflication()==Affliction::Pain);
//        CHECK_THROWS(inventory.findSubstitute(ptr5));
        auto randomWithAffliction = inventory.findRandomMedicine(Affliction::Ache);
        CHECK(randomWithAffliction->getAfflication()==Affliction::Ache);
//        auto randomMedicine = inventory.findRandomMedicine();
    }
}