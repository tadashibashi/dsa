#include "dsa_tests.h"
#include <dsa/vector.h>

TEST_CASE("vector tests")
{
    SECTION("emplacement")
    {
        vector<int> nums;
        REQUIRE(nums.size() == 0);
        REQUIRE(nums.empty());

        nums.emplace_back(0);
        REQUIRE(!nums.empty());
        REQUIRE(nums.size() == 1);
        REQUIRE(nums[0] == 0);

        nums.emplace_back(1);
        REQUIRE(nums.size() == 2);
        REQUIRE(nums[1] == 1);

        nums.emplace_back(2);
        REQUIRE(nums.size() == 3);
        REQUIRE(nums[2] == 2);

        nums.emplace_back(3);
        REQUIRE(nums.size() == 4);
        REQUIRE(nums[3] == 3);

        nums.clear();
        REQUIRE(nums.empty());
        REQUIRE(nums.size() == 0);
        REQUIRE_THROWS(nums.at(0));
    }

    SECTION("erase one")
    {
        SECTION("first")
        {
            vector<int> nums;
            nums.emplace_back(0);
            nums.emplace_back(1);
            nums.emplace_back(2);

            REQUIRE(nums[0] == 0);
            REQUIRE(nums[1] == 1);
            REQUIRE(nums[2] == 2);
            REQUIRE(nums.size() == 3);

            nums.erase(nums.begin());
            REQUIRE(nums.size() == 2);
            REQUIRE(nums[0] == 1);
            REQUIRE(nums[1] == 2);
        }

        SECTION("middle")
        {
            vector<int> nums;
            nums.emplace_back(0);
            nums.emplace_back(1);
            nums.emplace_back(2);

            REQUIRE(nums[0] == 0);
            REQUIRE(nums[1] == 1);
            REQUIRE(nums[2] == 2);
            REQUIRE(nums.size() == 3);

            nums.erase(nums.begin() + 1);
            REQUIRE(nums.size() == 2);
            REQUIRE(nums[0] == 0);
            REQUIRE(nums[1] == 2);
        }

        SECTION("last")
        {
            vector<int> nums;
            nums.emplace_back(0);
            nums.emplace_back(1);
            nums.emplace_back(2);

            REQUIRE(nums[0] == 0);
            REQUIRE(nums[1] == 1);
            REQUIRE(nums[2] == 2);
            REQUIRE(nums.size() == 3);

            nums.erase(nums.begin() + 2);
            REQUIRE(nums.size() == 2);
            REQUIRE(nums[0] == 0);
            REQUIRE(nums[1] == 1);
        }
    }

    SECTION("erase range")
    {
        SECTION("first")
        {
            vector<int> nums;
            nums.emplace_back(0);
            nums.emplace_back(1);
            nums.emplace_back(2);
            nums.emplace_back(3);

            REQUIRE(nums.size() == 4);

            nums.erase(nums.begin(), nums.begin() + 3);
            REQUIRE(nums.size() == 1);
            REQUIRE(nums[0] == 3);
        }

        SECTION("middle")
        {
            vector<int> nums;
            nums.emplace_back(0);
            nums.emplace_back(1);
            nums.emplace_back(2);
            nums.emplace_back(3);

            REQUIRE(nums.size() == 4);

            nums.erase(nums.begin() + 1, nums.begin() + 3);
            REQUIRE(nums.size() == 2);
            REQUIRE(nums[0] == 0);
            REQUIRE(nums[1] == 3);
        }

        SECTION("last")
        {
            vector<int> nums;
            nums.emplace_back(0);
            nums.emplace_back(1);
            nums.emplace_back(2);
            nums.emplace_back(3);

            REQUIRE(nums.size() == 4);

            nums.erase(nums.begin() + 1, nums.end());
            REQUIRE(nums.size() == 1);
            REQUIRE(nums[0] == 0);
        }
    }
}