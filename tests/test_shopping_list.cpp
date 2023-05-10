#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "../include/shopping_item.h"
#include "../include/shopping_list.h"

#include "../include/capsules.h"
#include "../include/drops.h"
#include "../include/ointment.h"
#include "../include/powders.h"
#include "../include/syrup.h"
#include "../include/tablets.h"

#include <memory>


TEST_CASE("shopping item simple tests", "[shopping item]") {
	std::shared_ptr<Medicine> Capsules1 = std::make_shared<Capsules>("Capsules1", Affliction::Ache, ActiveSubstance::Aspirin, 200, Price(16, 99), 100, 30);
	std::shared_ptr<Medicine> Tablets1 = std::make_shared<Tablets>("Tablets1", Affliction::Allergy, ActiveSubstance::Sertraline, 560, Price(27, 55), 100, 50);
	ShoppingItem Medicine1(Capsules1, 3);
	ShoppingItem Medicine2(Tablets1, 2);
	
	CHECK(Medicine1.getMedicinePtr() == Capsules1);
	CHECK(Medicine1.getNumberOfMedicines() == 3);
	
	CHECK(Medicine2.getMedicinePtr() == Tablets1);
	CHECK(Medicine2.getNumberOfMedicines() == 2);

	SECTION("testing comapring") {
		ShoppingItem Medicine3(Tablets1, 2);
		CHECK(Medicine3.getMedicinePtr() == Tablets1);
		CHECK(Medicine3.getNumberOfMedicines() == 2);
		CHECK_FALSE(Medicine1 == Medicine2);
		CHECK(Medicine1 != Medicine2);
		CHECK(Medicine2 == Medicine3);
		CHECK_FALSE(Medicine2 != Medicine3);
	} 

	SECTION("testing setting new pointer") {
		std::shared_ptr<Medicine> Syrup1 = std::make_shared<Syrup>("Syrup1", Affliction::Bellyache, ActiveSubstance::Sertraline, 500, Price(80, 00), 100, 500);
		Medicine2.setMedicinePtr(Syrup1);
		CHECK(Medicine2 == ShoppingItem(Syrup1, 2));
	}
}

TEST_CASE("shopping list simple tests", "[shopping list]") {
	std::shared_ptr<Medicine> Capsules1 = std::make_shared<Capsules>("Capsules1", Affliction::Ache, ActiveSubstance::Aspirin, 200, Price(16, 99), 100, 30);
	std::shared_ptr<Medicine> Drops1 = std::make_shared<Drops>("Drops1", Affliction::Pain, ActiveSubstance::Metformin, 1000, Price(23, 00), 100, 100);
	std::shared_ptr<Medicine> Ointment1 = std::make_shared<Ointment>("Ointment1", Affliction::Allergy, ActiveSubstance::Metamizole, 200, Price(30, 50), 100, 500);
	std::shared_ptr<Medicine> Powders1 = std::make_shared<Powders>("Powders1", Affliction::Bump, ActiveSubstance::Omeprazole, 1000, Price(45, 55), 100, 20);
	std::shared_ptr<Medicine> Syrup1 = std::make_shared<Syrup>("Syrup1", Affliction::Bellyache, ActiveSubstance::Sertraline, 500, Price(80, 00), 100, 500);
	std::shared_ptr<Medicine> Tablets1 = std::make_shared<Tablets>("Tablets1", Affliction::Allergy, ActiveSubstance::Sertraline, 560, Price(27, 55), 100, 50);
	std::shared_ptr<Medicine> Capsules2 = std::make_shared<Capsules>("Capsules2", Affliction::Backache, ActiveSubstance::Ibuprofen, 1200, Price(12, 59), 200, 20);
	std::shared_ptr<Medicine> Drops2 = std::make_shared<Drops>("Drops2", Affliction::Poisoning, ActiveSubstance::Amoxicillin, 500, Price(24, 50), 200, 150);
	std::shared_ptr<Medicine> Ointment2 = std::make_shared<Ointment>("Ointment2", Affliction::Cold, ActiveSubstance::Paracetamol, 600, Price(12, 50), 200, 300);
	std::shared_ptr<Medicine> Powders2 = std::make_shared<Powders>("Powders2", Affliction::Diarrhoea, ActiveSubstance::Acenocoumarol, 60, Price(36, 60), 200, 15);
	std::shared_ptr<Medicine> Syrup2 = std::make_shared<Syrup>("Syrup2", Affliction::Concussion, ActiveSubstance::Atorvastatin, 800, Price(67, 50), 200, 350);
	std::shared_ptr<Medicine> Tablets2 = std::make_shared<Tablets>("Tablets2", Affliction::Rash, ActiveSubstance::Omeprazole, 300, Price(18, 60), 200, 30);
	
	ShoppingItem Medicine1(Capsules1, 3);
	ShoppingItem Medicine2(Drops1, 2);
	ShoppingItem Medicine3(Ointment1, 3);
	ShoppingItem Medicine4(Powders1, 3);
	ShoppingItem Medicine5(Syrup1, 2);
	ShoppingItem Medicine6(Tablets1, 2);
	ShoppingItem Medicine7(Capsules2, 3);
	ShoppingItem Medicine8(Drops2, 2);
	ShoppingItem Medicine9(Ointment2, 3);
	ShoppingItem Medicine10(Powders2, 3);
	ShoppingItem Medicine11(Syrup2, 2);
	ShoppingItem Medicine12(Tablets2, 2);

	ShoppingList MareksList;

	MareksList.addMedicineToList(Capsules1, 3);
	CHECK(MareksList.getMedicinesList() == std::list<ShoppingItem>{Medicine1});
	MareksList.addMedicineToList(Drops1, 2);
	CHECK(MareksList.getMedicinesList() == std::list<ShoppingItem>{Medicine1, Medicine2});
	MareksList.addMedicineToList(Ointment1, 3);
	CHECK(MareksList.getMedicinesList() == std::list<ShoppingItem>{Medicine1, Medicine2, Medicine3});
	MareksList.addMedicineToList(Powders1, 3);
	CHECK(MareksList.getMedicinesList() == std::list<ShoppingItem>{Medicine1, Medicine2, Medicine3, Medicine4});
	MareksList.addMedicineToList(Syrup1, 2);
	CHECK(MareksList.getMedicinesList() == std::list<ShoppingItem>{Medicine1, Medicine2, Medicine3, Medicine4, Medicine5});
	MareksList.addMedicineToList(Tablets1, 2);
	CHECK(MareksList.getMedicinesList() == std::list<ShoppingItem>{Medicine1, Medicine2, Medicine3, Medicine4, Medicine5, Medicine6});
	MareksList.replaceMedicineInList(Capsules1, Capsules2);
	CHECK(MareksList.getMedicinesList() == std::list<ShoppingItem>{Medicine7, Medicine2, Medicine3, Medicine4, Medicine5, Medicine6});
	MareksList.replaceMedicineInList(Drops1, Drops2);
	CHECK(MareksList.getMedicinesList() == std::list<ShoppingItem>{Medicine7, Medicine8, Medicine3, Medicine4, Medicine5, Medicine6});
	MareksList.replaceMedicineInList(Ointment1, Ointment2);
	CHECK(MareksList.getMedicinesList() == std::list<ShoppingItem>{Medicine7, Medicine8, Medicine9, Medicine4, Medicine5, Medicine6});
	MareksList.replaceMedicineInList(Powders1, Powders2);
	CHECK(MareksList.getMedicinesList() == std::list<ShoppingItem>{Medicine7, Medicine8, Medicine9, Medicine10, Medicine5, Medicine6});
	MareksList.replaceMedicineInList(Syrup1, Syrup2);
	CHECK(MareksList.getMedicinesList() == std::list<ShoppingItem>{Medicine7, Medicine8, Medicine9, Medicine10, Medicine11, Medicine6});
	MareksList.replaceMedicineInList(Tablets1, Tablets2);
	CHECK(MareksList.getMedicinesList() == std::list<ShoppingItem>{Medicine7, Medicine8, Medicine9, Medicine10, Medicine11, Medicine12});
}