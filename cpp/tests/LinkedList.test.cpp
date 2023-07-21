#include <catch2/catch_test_macros.hpp>
#include <dsa/data/LinkedList.h>


TEST_CASE( "LinkedList" ) {

    dsa::LinkedList<int> list;

    SECTION("initialized size is 0") {
        REQUIRE(list.size() == 0);
    }

    SECTION("indexing a zero-length list throws") {
        REQUIRE_THROWS(list[0]);
    }

    SECTION("appending increases list size") {
        list.append(0);
        REQUIRE(list.size() == 1);
    }
}
