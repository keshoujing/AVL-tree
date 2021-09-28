#include "testFunction.h"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("test_insert")
{
    //insert 100;
    REQUIRE(test_insert() == 100);
}

TEST_CASE("test_remove")
{
    //insert 100 and remove 99.
    REQUIRE(test_remove() == 1);
}

TEST_CASE("test_removeInorder")
{
    //insert 30 and (removeInorder 0) * 20.
    REQUIRE(test_removeInorder() == 10);
}

TEST_CASE("test_root_afterInsert")
{
    //insert 10 node and calculate root by hand. return gatorID.
    REQUIRE(test_insert_RootNode() == 45005211);
}

TEST_CASE("test_root_afterRemove")
{
    //insert 10 node and remove the root node, calculate new root by hand. return gatorID.
    REQUIRE(test_remove_RootNode() == 53455736);
}