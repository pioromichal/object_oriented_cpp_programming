#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "../include/client.h"
#include "../include/business_client.h"
#include "../include/individual_client.h"
#include "../include/capsules.h"
#include "../include/tablets.h"


TEST_CASE("Client simple tests", "[client]") {
	std::shared_ptr<Medicine> Capsules1 = std::make_shared<Capsules>("Capsules1", Affliction::Ache, ActiveSubstance::Aspirin, 200, Price(16, 99), 100, 30);
	std::shared_ptr<Medicine> Tablets1 = std::make_shared<Tablets>("Tablets1", Affliction::Allergy, ActiveSubstance::Sertraline, 560, Price(27, 55), 100, 50);

	ShoppingList JansList;
	JansList.addMedicineToList(Capsules1, 3);

	IndividualClient JanK("Jan", "Kowalski", JansList, 0.789);

	CHECK(JanK.getName() == "Jan");
	CHECK(JanK.getSurame() == "Kowalski");
	CHECK(JanK.getShoppingList().getMedicinesList() == std::list<ShoppingItem>{ShoppingItem(Capsules1, 3)});
	CHECK(std::abs(JanK.getProbabilityOfActions() - 0.789) < 0.001);

	SECTION("testing replacing medicine on list") {
		JanK.replaceMedicineOnList(Capsules1, Tablets1);
		CHECK(JanK.getName() == "Jan");
		CHECK(JanK.getSurame() == "Kowalski");
		CHECK(JanK.getShoppingList().getMedicinesList() == std::list<ShoppingItem>{ShoppingItem(Tablets1, 3)});
		CHECK(std::abs(JanK.getProbabilityOfActions() - 0.789) < 0.001);
	}

	SECTION("testing adding medicine to list") {
		JanK.addMedicineToList(Tablets1, 5);
		CHECK(JanK.getName() == "Jan");
		CHECK(JanK.getSurame() == "Kowalski");
		CHECK(JanK.getShoppingList().getMedicinesList() == std::list<ShoppingItem>{ShoppingItem(Capsules1, 3), ShoppingItem(Tablets1, 5)});
		CHECK(std::abs(JanK.getProbabilityOfActions() - 0.789) < 0.001);
	}

	SECTION("testing adding existing on list medicine to list") {
		JanK.addMedicineToList(Capsules1, 5);
		CHECK(JanK.getName() == "Jan");
		CHECK(JanK.getSurame() == "Kowalski");
		CHECK(JanK.getShoppingList().getMedicinesList() == std::list<ShoppingItem>{ShoppingItem(Capsules1, 8)});
		CHECK(std::abs(JanK.getProbabilityOfActions() - 0.789) < 0.001);
	}

	SECTION("testing calculating netto price ic") {
		CHECK(JanK.calculateNettoPrice() == Price(53, 49));
		JanK.addMedicineToList(Tablets1, 5);
		CHECK(JanK.calculateNettoPrice() == Price(195, 34));
	}

	SECTION("testing calculating tax ic") {
		CHECK(JanK.calculateTax() == Price(12, 30));
		JanK.addMedicineToList(Tablets1, 5);
		CHECK(JanK.calculateTax() == Price(44, 92));
	}

	SECTION("testing calculating brutto price ic") {
		CHECK(JanK.calculateBruttoPrice() == Price(65, 79));
		JanK.addMedicineToList(Tablets1, 5);
		CHECK(JanK.calculateBruttoPrice() == Price(240, 26));
	}
	SECTION("testing business client") {
		ShoppingList PiotrsList;
		PiotrsList.addMedicineToList(Tablets1, 4);

		BusinessClient PiotrN("Piotr", "Nowak", PiotrsList, 0.345);

		CHECK(PiotrN.getName() == "Piotr");
		CHECK(PiotrN.getSurame() == "Nowak");
		CHECK(PiotrN.getShoppingList().getMedicinesList() == std::list<ShoppingItem>{ShoppingItem(Tablets1, 4)});
		CHECK(std::abs(PiotrN.getProbabilityOfActions() - 0.345) < 0.001);

		SECTION("testing calculating netto price bc") {
			CHECK(PiotrN.calculateNettoPrice() == Price(113, 48));
			PiotrN.addMedicineToList(Capsules1, 5);
			CHECK(PiotrN.calculateNettoPrice() == Price(202, 63));
		}

		SECTION("testing calculating tax bc") {
			CHECK(PiotrN.calculateTax() == Price(9, 7));
			PiotrN.addMedicineToList(Capsules1, 5);
			CHECK(PiotrN.calculateTax() == Price(16, 21));
		}

		SECTION("testing calculating brutto price bc") {
			CHECK(PiotrN.calculateBruttoPrice() == Price(122, 55));
			PiotrN.addMedicineToList(Capsules1, 5);
			CHECK(PiotrN.calculateBruttoPrice() == Price(218, 84));
		}
	}
}
