#include <catch2/catch_test_macros.hpp>
#include <dsa/data/LinkedList.h>

TEST_CASE( "LinkedList initializes at size zero" ) {
    dsa::LinkedList<int> list;
    REQUIRE(list.size() == 0);
}
