#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "../include/medicine.h"
#include "../include/capsules.h"
#include "../include/drops.h"
#include "../include/ointment.h"
#include "../include/powders.h"
#include "../include/syrup.h"
#include "../include/tablets.h"

TEST_CASE("capsules simple tests", "[capsules]") {
	Medicine::resetMedId();
	Capsules Capsules1("Capsules1", Affliction::Ache, ActiveSubstance::Aspirin, 200, Price(16, 99), 100, 30);
	Capsules Capsules2("Capsules2", Affliction::Backache, ActiveSubstance::Ibuprofen, 1200, Price(12, 59), 200, 20);
	CHECK(Capsules1.getId() == 1);
	CHECK(Capsules1.getName() == "Capsules1");
	CHECK(Capsules1.getAfflication() == Affliction::Ache);
	CHECK(Capsules1.getActiveSubstance() == ActiveSubstance::Aspirin);
	CHECK(Capsules1.getMiligramsOfActiveSubstance() == 200);
	CHECK(Capsules1.getBasePrice() == Price(16, 99));
	CHECK(Capsules1.getAmountInPharmacy() == 100);
	CHECK(Capsules1.getNumber() == 30);

	CHECK(Capsules2.getId() == 2);
	CHECK(Capsules2.getName() == "Capsules2");
	CHECK(Capsules2.getAfflication() == Affliction::Backache);
	CHECK(Capsules2.getActiveSubstance() == ActiveSubstance::Ibuprofen);
	CHECK(Capsules2.getMiligramsOfActiveSubstance() == 1200);
	CHECK(Capsules2.getBasePrice() == Price(12, 59));
	CHECK(Capsules2.getAmountInPharmacy() == 200);
	CHECK(Capsules2.getNumber() == 20);

	SECTION("testing operator--") {
		--Capsules1;
		CHECK(Capsules1.getId() == 1);
		CHECK(Capsules1.getName() == "Capsules1");
		CHECK(Capsules1.getAfflication() == Affliction::Ache);
		CHECK(Capsules1.getActiveSubstance() == ActiveSubstance::Aspirin);
		CHECK(Capsules1.getMiligramsOfActiveSubstance() == 200);
		CHECK(Capsules1.getBasePrice() == Price(16, 99));
		CHECK(Capsules1.getAmountInPharmacy() == 99);
		CHECK(Capsules1.getNumber() == 30);
		--Capsules1;
		CHECK(Capsules1.getId() == 1);
		CHECK(Capsules1.getName() == "Capsules1");
		CHECK(Capsules1.getAfflication() == Affliction::Ache);
		CHECK(Capsules1.getActiveSubstance() == ActiveSubstance::Aspirin);
		CHECK(Capsules1.getMiligramsOfActiveSubstance() == 200);
		CHECK(Capsules1.getBasePrice() == Price(16, 99));
		CHECK(Capsules1.getAmountInPharmacy() == 98);
		CHECK(Capsules1.getNumber() == 30);
	}

	SECTION("testing calculating price") {
		CHECK(Capsules1.calculatePrice() == Price(17, 83));
		CHECK(Capsules2.calculatePrice() == Price(13, 21));
	}

	SECTION("testing checking is on prescription") {
		CHECK_FALSE(Capsules1.checkIsOnPrescription());
		CHECK(Capsules2.checkIsOnPrescription());
	}

	SECTION("testing string representation") {
		CHECK(Capsules1.representAsString() == "Capsules: Capsules1 (1)\nPrescription: no\nTreated affliction: Ache\nNumber of capsules: 30\nOne capsule contains 200 mg of Aspirin\nPrise: 17,83 PLN\n");
	}
}

TEST_CASE("Drops simple tests", "[drops]") {
	Medicine::resetMedId();
	Drops Drops1("Drops1", Affliction::Pain, ActiveSubstance::Metformin, 1000, Price(23, 00), 100, 100);
	Drops Drops2("Drops2", Affliction::Poisoning, ActiveSubstance::Amoxicillin, 500, Price(24, 50), 200, 150);
	CHECK(Drops1.getId() == 1);
	CHECK(Drops1.getName() == "Drops1");
	CHECK(Drops1.getAfflication() == Affliction::Pain);
	CHECK(Drops1.getActiveSubstance() == ActiveSubstance::Metformin);
	CHECK(Drops1.getMiligramsOfActiveSubstance() == 1000);
	CHECK(Drops1.getBasePrice() == Price(23, 00));
	CHECK(Drops1.getAmountInPharmacy() == 100);
	CHECK(Drops1.getVolumeInMilliliters() == 100);

	CHECK(Drops2.getId() == 2);
	CHECK(Drops2.getName() == "Drops2");
	CHECK(Drops2.getAfflication() == Affliction::Poisoning);
	CHECK(Drops2.getActiveSubstance() == ActiveSubstance::Amoxicillin);
	CHECK(Drops2.getMiligramsOfActiveSubstance() == 500);
	CHECK(Drops2.getBasePrice() == Price(24, 50));
	CHECK(Drops2.getAmountInPharmacy() == 200);
	CHECK(Drops2.getVolumeInMilliliters() == 150);

	SECTION("testing calculating price") {
		CHECK(Drops1.calculatePrice() == Price(25, 30));
		CHECK(Drops2.calculatePrice() == Price(26, 95));
	}

	SECTION("testing checking is on prescription") {
		CHECK(Drops1.checkIsOnPrescription());
		CHECK(Drops2.checkIsOnPrescription());
	}

	SECTION("testing string representation") {
		CHECK(Drops1.representAsString() == "Drops: Drops1 (1)\nPrescription: no\nTreated affliction: Pain\nVolume: 100 ml\nOne dose contains 1000 mg of Metformin\nPrise: 25,30 PLN\n");
	}
}

TEST_CASE("ointment simple tests", "[ointment]") {
	Medicine::resetMedId();
	Ointment Ointment1("Ointment1", Affliction::Allergy, ActiveSubstance::Metamizole, 200, Price(30, 50), 100, 500);
	Ointment Ointment2("Ointment2", Affliction::Cold, ActiveSubstance::Paracetamol, 600, Price(12, 50), 200, 300);
	CHECK(Ointment1.getId() == 1);
	CHECK(Ointment1.getName() == "Ointment1");
	CHECK(Ointment1.getAfflication() == Affliction::Allergy);
	CHECK(Ointment1.getActiveSubstance() == ActiveSubstance::Metamizole);
	CHECK(Ointment1.getMiligramsOfActiveSubstance() == 200);
	CHECK(Ointment1.getBasePrice() == Price(30, 50));
	CHECK(Ointment1.getAmountInPharmacy() == 100);
	CHECK(Ointment1.getVolumeInMilliliters() == 500);

	CHECK(Ointment2.getId() == 2);
	CHECK(Ointment2.getName() == "Ointment2");
	CHECK(Ointment2.getAfflication() == Affliction::Cold);
	CHECK(Ointment2.getActiveSubstance() == ActiveSubstance::Paracetamol);
	CHECK(Ointment2.getMiligramsOfActiveSubstance() == 600);
	CHECK(Ointment2.getBasePrice() == Price(12, 50));
	CHECK(Ointment2.getAmountInPharmacy() == 200);
	CHECK(Ointment2.getVolumeInMilliliters() == 300);

	SECTION("testing calculating price") {
		CHECK(Ointment1.calculatePrice() == Price(32, 94));
		CHECK(Ointment2.calculatePrice() == Price(13, 50));
	}

	SECTION("testing checking is on prescription") {
		CHECK_FALSE(Ointment1.checkIsOnPrescription());
		CHECK_FALSE(Ointment2.checkIsOnPrescription());
	}

	SECTION("testing string representation") {
		CHECK(Ointment1.representAsString() == "Ointment: Ointment1 (1)\nPrescription: no\nTreated affliction: Allergy\nVolume: 500 ml\nOne dose contains 200 mg of Metamizole\nPrise: 32,94 PLN\n");
	}
}

TEST_CASE("powders simple tests", "[powders]") {
	Medicine::resetMedId();
	Powders Powders1("Powders1", Affliction::Bump, ActiveSubstance::Omeprazole, 1000, Price(45, 55), 100, 20);
	Powders Powders2("Powders2", Affliction::Diarrhoea, ActiveSubstance::Acenocoumarol, 60, Price(36, 60), 200, 15);
	CHECK(Powders1.getId() == 1);
	CHECK(Powders1.getName() == "Powders1");
	CHECK(Powders1.getAfflication() == Affliction::Bump);
	CHECK(Powders1.getActiveSubstance() == ActiveSubstance::Omeprazole);
	CHECK(Powders1.getMiligramsOfActiveSubstance() == 1000);
	CHECK(Powders1.getBasePrice() == Price(45, 55));
	CHECK(Powders1.getAmountInPharmacy() == 100);
	CHECK(Powders1.getNumberOfSachets() == 20);

	CHECK(Powders2.getId() == 2);
	CHECK(Powders2.getName() == "Powders2");
	CHECK(Powders2.getAfflication() == Affliction::Diarrhoea);
	CHECK(Powders2.getActiveSubstance() == ActiveSubstance::Acenocoumarol);
	CHECK(Powders2.getMiligramsOfActiveSubstance() == 60);
	CHECK(Powders2.getBasePrice() == Price(36, 60));
	CHECK(Powders2.getAmountInPharmacy() == 200);
	CHECK(Powders2.getNumberOfSachets() == 15);

	SECTION("testing calculating price") {
		CHECK(Powders1.calculatePrice() == Price(51, 92));
		CHECK(Powders2.calculatePrice() == Price(41, 72));
	}

	SECTION("testing checking is on prescription") {
		CHECK(Powders1.checkIsOnPrescription());
		CHECK_FALSE(Powders2.checkIsOnPrescription());
	}

	SECTION("testing string representation") {
		CHECK(Powders1.representAsString() == "Powders: Powders1 (1)\nPrescription: no\nTreated affliction: Bump\nNumber of sachets: 20\nOne sachet contains 1000 mg of Omeprazole\nPrise: 51,92 PLN\n");
	}
}

TEST_CASE("Syrup simple tests", "[syrup]") {
	Medicine::resetMedId();
	Syrup Syrup1("Syrup1", Affliction::Bellyache, ActiveSubstance::Sertraline, 500, Price(80, 00), 100, 500);
	Syrup Syrup2("Syrup2", Affliction::Concussion, ActiveSubstance::Atorvastatin, 800, Price(67, 50), 200, 350);
	CHECK(Syrup1.getId() == 1);
	CHECK(Syrup1.getName() == "Syrup1");
	CHECK(Syrup1.getAfflication() == Affliction::Bellyache);
	CHECK(Syrup1.getActiveSubstance() == ActiveSubstance::Sertraline);
	CHECK(Syrup1.getMiligramsOfActiveSubstance() == 500);
	CHECK(Syrup1.getBasePrice() == Price(80, 00));
	CHECK(Syrup1.getAmountInPharmacy() == 100);
	CHECK(Syrup1.getVolumeInMilliliters() == 500);

	CHECK(Syrup2.getId() == 2);
	CHECK(Syrup2.getName() == "Syrup2");
	CHECK(Syrup2.getAfflication() == Affliction::Concussion);
	CHECK(Syrup2.getActiveSubstance() == ActiveSubstance::Atorvastatin);
	CHECK(Syrup2.getMiligramsOfActiveSubstance() == 800);
	CHECK(Syrup2.getBasePrice() == Price(67, 50));
	CHECK(Syrup2.getAmountInPharmacy() == 200);
	CHECK(Syrup2.getVolumeInMilliliters() == 350);

	SECTION("testing calculating price") {
		CHECK(Syrup1.calculatePrice() == Price(85, 60));
		CHECK(Syrup2.calculatePrice() == Price(72, 22));
	}

	SECTION("testing checking is on prescription") {
		CHECK(Syrup1.checkIsOnPrescription());
		CHECK(Syrup2.checkIsOnPrescription());
	}

	SECTION("testing string representation") {
		CHECK(Syrup1.representAsString() == "Syrup: Syrup1 (1)\nPrescription: no\nTreated affliction: Bellyache\nVolume: 500 ml\nOne dose contains 500 mg of Sertraline\nPrise: 85,60 PLN\n");
	}
}

TEST_CASE("tablets simple tests", "[tablets]") {
	Medicine::resetMedId();
	Tablets Tablets1("Tablets1", Affliction::Bleeding, ActiveSubstance::Sertraline, 560, Price(27, 55), 100, 50);
	Tablets Tablets2("Tablets2", Affliction::Rash, ActiveSubstance::Omeprazole, 300, Price(18, 60), 200, 30);
	CHECK(Tablets1.getId() == 1);
	CHECK(Tablets1.getName() == "Tablets1");
	CHECK(Tablets1.getAfflication() == Affliction::Bleeding);
	CHECK(Tablets1.getActiveSubstance() == ActiveSubstance::Sertraline);
	CHECK(Tablets1.getMiligramsOfActiveSubstance() == 560);
	CHECK(Tablets1.getBasePrice() == Price(27, 55));
	CHECK(Tablets1.getAmountInPharmacy() == 100);
	CHECK(Tablets1.getNumber() == 50);

	CHECK(Tablets2.getId() == 2);
	CHECK(Tablets2.getName() == "Tablets2");
	CHECK(Tablets2.getAfflication() == Affliction::Rash);
	CHECK(Tablets2.getActiveSubstance() == ActiveSubstance::Omeprazole);
	CHECK(Tablets2.getMiligramsOfActiveSubstance() == 300);
	CHECK(Tablets2.getBasePrice() == Price(18, 60));
	CHECK(Tablets2.getAmountInPharmacy() == 200);
	CHECK(Tablets2.getNumber() == 30);

	SECTION("testing calculating price") {
		CHECK(Tablets1.calculatePrice() == Price(28, 37));
		CHECK(Tablets2.calculatePrice() == Price(19, 15));
	}

	SECTION("testing checking is on prescription") {
		CHECK(Tablets1.checkIsOnPrescription());
		CHECK(Tablets2.checkIsOnPrescription());
	}

	SECTION("testing string representation") {
		CHECK(Tablets1.representAsString() == "Tablets: Tablets1 (1)\nPrescription: no\nTreated affliction: Bleeding\nNumber of tablets: 50\nOne tablet contains 560 mg of Sertraline\nPrise: 28,37 PLN\n");
	}
}