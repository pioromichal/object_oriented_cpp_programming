#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "../include/counter.h"
#include "../include/counters_list.h"
TEST_CASE("Test Counter_list") {
        Counter::resetIdNumbering();
        CountersList countersList(5, 3);
    SECTION("Test constructor`"){
        REQUIRE(countersList.getSet().size() == 5);
        CHECK(countersList.getCounter(1)->isOpened());
        CHECK(countersList.getCounter(2)->isOpened());
        CHECK(countersList.getCounter(3)->isOpened());
        CHECK_FALSE(countersList.getCounter(4)->isOpened());
        CHECK_FALSE(countersList.getCounter(5)->isOpened());
        CHECK(countersList.getCounter(1)->getTimeOpened()==0);
        CHECK(countersList.getCounter(4)->getTimeOpened()==0);
        CHECK_FALSE(countersList.getCounter(2)->isOccupied());
        CHECK_FALSE(countersList.getCounter(5)->isOccupied());
        CHECK(countersList.getOpenedCounters()==3);

    }SECTION("Test counter time open"){
        countersList.nextTurn();
        CHECK(countersList.getCounter(1)->getTimeOpened()==1);
        CHECK(countersList.getCounter(4)->getTimeOpened()==0);
        countersList.nextTurn();
        countersList.nextTurn();
        CHECK(countersList.getCounter(1)->getTimeOpened()==3);
        CHECK(countersList.getCounter(4)->getTimeOpened()==0);
    }SECTION("Test opening and closing counters"){
        CHECK(countersList.getCounter(3)->isOpened());
        CHECK_FALSE(countersList.getCounter(4)->isOpened());
        countersList.openCounter(4);
        CHECK(countersList.getCounter(4)->isOpened());
        countersList.closeCounter(3);
        CHECK_FALSE(countersList.getCounter(3)->isOpened());
    }SECTION("Longest working"){
        countersList.closeCounter(2);
        countersList.nextTurn();
        countersList.nextTurn();
        countersList.closeCounter(3);
        countersList.openCounter(2);
        countersList.nextTurn();
        countersList.nextTurn();
        CHECK(countersList.getCounter(3)->getTimeOpened()==0);
        CHECK(countersList.getCounter(2)->getTimeOpened()==2);
        CHECK(countersList.findLongestWorking()->getTimeOpened()==4);
        CHECK(countersList.findLongestWorking()->getId()==1);
    }
}