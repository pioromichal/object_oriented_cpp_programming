#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "../include/counter.h"
TEST_CASE("Test Counter"){
    Counter::resetIdNumbering();
    Counter a1 = Counter(false);
    Counter b2 = Counter(true);
    SECTION("Constructor and getters"){
        CHECK(a1.getTimeOpened()==0);
        CHECK(b2.isOpened());
        CHECK_FALSE(a1.isOpened());
        REQUIRE(a1.getId()==1);
        REQUIRE(b2.getId()==2);
    }SECTION("Comparator and increment"){
        a1++;
        a1++;
        a1++;
        b2++;
        CHECK(a1<b2);
        CHECK_FALSE(b2<a1);
        CHECK(a1.getTimeOpened()==3);
        CHECK(b2.getTimeOpened()==1);
    }SECTION("Opening and closing counter"){
        CHECK_FALSE(a1.isOpened());
        a1.openCounter();
        CHECK(a1.isOpened());
        CHECK(b2.isOpened());
        b2.openCounter();
        CHECK(b2.isOpened());
        a1.closeCounter();
        CHECK_FALSE(a1.isOpened());
        a1.closeCounter();
        CHECK_FALSE(a1.isOpened());
    }
}