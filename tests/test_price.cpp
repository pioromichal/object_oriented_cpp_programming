#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "../include/price.h"

TEST_CASE("Price simple test", "[Price]") {
    Price Price1(1345, 34);
    Price Price2(1345, 178);
    CHECK(Price1.getZlotys() == 1345);
    CHECK(Price1.getGrosze() == 34);
    CHECK(Price2.getZlotys() == 1346);
    CHECK(Price2.getGrosze() == 78);
    SECTION("setting new value of zlotys") {
        Price1.setZlotys(3450);
        Price2.setZlotys(7462);
        CHECK(Price1.getZlotys() == 3450);
        CHECK(Price1.getGrosze() == 34);
        CHECK(Price2.getZlotys() == 7462);
        CHECK(Price2.getGrosze() == 78);
    }
    SECTION("setting new value of grosze") {
        Price1.setGrosze(456);
        Price2.setGrosze(4);
        CHECK(Price1.getZlotys() == 1349);
        CHECK(Price1.getGrosze() == 56);
        CHECK(Price2.getZlotys() == 1346);
        CHECK(Price2.getGrosze() == 4);
    }
    SECTION("comaparing tests") {
        CHECK(Price1 != Price2);
        CHECK_FALSE(Price1 == Price2);
        CHECK(Price1 < Price2);
        CHECK_FALSE(Price1 > Price2);
        CHECK(Price1 <= Price2);
        CHECK_FALSE(Price1 >= Price2);
        CHECK_FALSE(Price2 < Price1);
        CHECK(Price2 > Price1);
        CHECK_FALSE(Price2 <= Price1);
        CHECK(Price2 >= Price1);
    }
    SECTION("comaparing tests 2 equal salaries") {
        Price2.setZlotys(1345);
        Price2.setGrosze(34);
        CHECK(Price1 == Price2);
        CHECK_FALSE(Price1 != Price2);
        CHECK_FALSE(Price1 < Price2);
        CHECK_FALSE(Price1 > Price2);
        CHECK(Price1 <= Price2);
        CHECK(Price1 >= Price2);
        CHECK_FALSE(Price2 < Price1);
        CHECK_FALSE(Price2 > Price1);
        CHECK(Price2 <= Price1);
        CHECK(Price2 >= Price1);
    }
    SECTION("adding to existing Price another") {
        Price1 += Price2;
        CHECK(Price1.getZlotys() == 2692);
        CHECK(Price1.getGrosze() == 12);
        CHECK(Price2.getZlotys() == 1346);
        CHECK(Price2.getGrosze() == 78);
    }
    SECTION("adding two Prices") {
        Price Price3(0, 0);
        Price3 = Price1 + Price2;
        CHECK(Price1.getZlotys() == 1345);
        CHECK(Price1.getGrosze() == 34);
        CHECK(Price2.getZlotys() == 1346);
        CHECK(Price2.getGrosze() == 78);
        CHECK(Price3.getZlotys() == 2692);
        CHECK(Price3.getGrosze() == 12);;
    }
    SECTION("substract from existing Price another") {
        Price2 -= Price1;
        CHECK(Price1.getZlotys() == 1345);
        CHECK(Price1.getGrosze() == 34);
        CHECK(Price2.getZlotys() == 1);
        CHECK(Price2.getGrosze() == 44);
    }
    SECTION("substracting two Prices") {
        Price Price3(0, 0);
        Price3 = Price2 - Price1;
        CHECK(Price1.getZlotys() == 1345);
        CHECK(Price1.getGrosze() == 34);
        CHECK(Price2.getZlotys() == 1346);
        CHECK(Price2.getGrosze() == 78);
        CHECK(Price3.getZlotys() == 1);
        CHECK(Price3.getGrosze() == 44);
    }
    SECTION("multiplying by unsigned int value") {
        Price Price_3(0, 0);
        Price_3 = Price1 * 4;
        CHECK(Price1.getZlotys() == 1345);
        CHECK(Price1.getGrosze() == 34);
        CHECK(Price_3.getZlotys() == 5381);
        CHECK(Price_3.getGrosze() == 36);
    }
    SECTION("dividing by unsigned int value") {
        Price Price_3(0, 0);
        Price_3 = Price2 / 2;
        CHECK(Price_3.getZlotys() == 673);
        CHECK(Price_3.getGrosze() == 39);
        CHECK(Price2.getZlotys() == 1346);
        CHECK(Price2.getGrosze() == 78);
    }
}