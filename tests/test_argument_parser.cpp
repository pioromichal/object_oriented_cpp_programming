#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "../include/arguments.h"
TEST_CASE("Test argument parser"){
    int argc = 3;
    char* argv[] = { "my_program", "--path", "test.json" };
    Arguments arguments(argc, argv);
    SECTION("JSON path"){
        CHECK(arguments.pathToJSON()=="test.json");
    }
}