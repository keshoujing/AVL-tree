#include "../main.cpp"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("input 1,3,5,7,9")
{
    AVL_Tree AVL;
    AVL.insert(123,"234");
    REQUIRE(AVL.checkNextHeight(AVL.getRoot()) == 1);
    REQUIRE_FALSE(AVL.checkNextHeight(AVL.getRoot()) != 1);
}
