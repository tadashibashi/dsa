#include <catch2/catch_test_macros.hpp>
#include <dsa/data/LinkedList.h>


TEST_CASE( "LinkedList" ) {

    dsa::LinkedList<int> list;

    SECTION("initialized size is 0") {
        REQUIRE(list.size() == 0);
        REQUIRE(list.empty());
    }

    SECTION("indexing a zero-length list throws") {
        REQUIRE_THROWS(list[0]);
    }

    SECTION("appending increases list size") {
        list.append(0);
        REQUIRE(list.size() == 1);
        REQUIRE(!list.empty());

        list.append(1);
        list.append(1241);
        list.append(-124123);
        list.append(999);
        REQUIRE(list.size() == 5);
    }

    SECTION("indexing an appended list works") {
        list.append(33);
        list.append(58);
        list.append(12389);
        list.append(-141);

        REQUIRE(list[0] == 33);
        REQUIRE(list[1] == 58);
        REQUIRE(list[2] == 12389);
        REQUIRE(list[3] == -141);
    }

    SECTION("insertion tests") {
        SECTION("insertion at zero is valid") {
            list.insert(0, 10);
            REQUIRE(list[0] == 10);
        }

        SECTION("inserting increases list size") {
            list.insert(0, 10);
            REQUIRE(list.size() == 1);
        }
    }

    SECTION("reverse") {
        SECTION("reverse one-length list") {
            list.append(0);
            list.reverse();
            REQUIRE(list.size() == 1);
            REQUIRE(list[0] == 0);
        }

        SECTION("reverse two-length list") {
            list.append(5);
            list.append(7);
            REQUIRE(list.size() == 2);
            REQUIRE(list[0] == 5);
            REQUIRE(list[1] == 7);

            list.reverse();

            REQUIRE(list.size() == 2);
            REQUIRE(list[0] == 7);
            REQUIRE(list[1] == 5);
        }

        SECTION("reverse 5-length list") {
            list.append(0);
            list.append(1);
            list.append(2);
            list.append(3);
            list.append(4);
            REQUIRE(list.size() == 5);
            REQUIRE(list[0] == 0);
            REQUIRE(list[2] == 2);
            REQUIRE(list[4] == 4);

            list.reverse();

            REQUIRE(list.size() == 5);
            REQUIRE(list[0] == 4);
            REQUIRE(list[2] == 2);
            REQUIRE(list[4] == 0);
        }


    }

}
