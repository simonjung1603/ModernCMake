#include <MidiMessage.h>

#include "doctest.h"

TEST_CASE("Class MidiMessage")
{
    auto msg = mb::MidiMessage();

    SUBCASE("Test getters")
    {
        CHECK(!msg);
        CHECK(msg.GetType() == mb::EVENT_TYPE::UNINITIALIZED);
        CHECK(msg.GetChannel() == 0);
        CHECK(msg.GetSecondByte() == 0);
        CHECK(msg.GetThirdByte() == 0);
    }

    SUBCASE("Test setters")
    {
        CHECK(true);
    }
}
