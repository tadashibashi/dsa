#include <catch2/catch_session.hpp>

int main(int argc, char *argv[])
{
    const auto result = Catch::Session().run(argc, argv);

    return result;
}