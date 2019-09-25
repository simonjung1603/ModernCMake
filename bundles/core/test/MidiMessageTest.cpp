#include <MidiMessage.h>

#include "doctest.h"

TEST_CASE("Class MidiMessage")
{
    SUBCASE("Test getters")
    {
        auto mm = mb::MidiMessage();
        CHECK(true);
    }
    
    SUBCASE("Test setters")
    {
        CHECK(true);
    }
}
