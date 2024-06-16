#include "dsa_tests.h"
#include <dsa/hash_map.h>

#include <iostream>
#include <string>
#include <unordered_map>

TEST_CASE("hash_map tests")
{
    SECTION("Emplacement")
    {
        hash_map<std::string, int> nums;

        REQUIRE(nums.empty());

        auto it = nums.emplace("Hello", 100);
        REQUIRE(it->first == "Hello");
        REQUIRE(it->second == 100);

        REQUIRE(!nums.empty());
        REQUIRE(nums.size() == 1);

        it = nums.emplace("World", 200);
        REQUIRE(it->first == "World");
        REQUIRE(it->second == 200);
        REQUIRE(nums.size() == 2);

        REQUIRE(nums.find("Hello") != nums.end());
        REQUIRE(nums.find("World") != nums.end());
        REQUIRE(nums.find("Pizza") == nums.end());

        nums.clear();
        REQUIRE(nums.empty());
        REQUIRE(nums.find("Hello") == nums.end());
        REQUIRE(nums.find("World") == nums.end());
    }

    SECTION("Range-based iterator")
    {
        hash_map<std::string, int> nums;
        nums.emplace("Beemo", 1234);
        nums.emplace("Mathematical", 777);
        nums.emplace("Pizza", 999);

        std::unordered_map<std::string, int> numsCheck;
        for (auto &[key, value] : nums)
        {
            numsCheck.emplace(key, value);
        }

        REQUIRE(numsCheck.size() == 3);
        REQUIRE(numsCheck["Beemo"] == 1234);
        REQUIRE(numsCheck["Mathematical"] == 777);
        REQUIRE(numsCheck["Pizza"] == 999);
    }

    SECTION("Move constructor gets called on emplacement")
    {
        struct MyStruct {
            MyStruct() = default;
            explicit MyStruct(int value, bool *destructorCalledOnMoved = nullptr) : value(value),
                destructorCalledOnMoved(destructorCalledOnMoved) { }
            MyStruct(const MyStruct &other) = default;
            MyStruct(MyStruct &&other) noexcept : value(other.value) {
                other.value = 0xbadbad;
            }
            ~MyStruct()
            {
                if (destructorCalledOnMoved && value == 0xbadbad)
                    *destructorCalledOnMoved = true;
            }

            int value{};
            bool *destructorCalledOnMoved{};
        };

        hash_map<int, MyStruct> structs;
        bool destructorCalledOnMoved = false;

        structs.emplace(100, MyStruct{20, &destructorCalledOnMoved});
        REQUIRE(destructorCalledOnMoved);

        auto it = structs.find(100);
        REQUIRE((it.isValid() && it->second.value == 20));
    }

    SECTION("Rehashing occurs when expected")
    {
        hash_map<int, int> structs(1, 1.f);
        REQUIRE(structs.bucket_count() == 1);

        structs.emplace(200, 1);
        structs.emplace(201, 2);

        REQUIRE(structs.bucket_count() > 1); // resizes past 1
    }
}
