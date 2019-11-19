#include <MidiMessage.h>

#include "doctest.h"

TEST_CASE("Class MidiMessage")
{
    auto msg = mb::MidiMessage();

    SUBCASE("Test uninitialized")
    {
        CHECK(!msg);
        CHECK(msg.GetType() == mb::EVENT_TYPE::UNINITIALIZED);
        CHECK(msg.GetChannel() == 0);
        CHECK(msg.GetFirstDataByte() == 0);
        CHECK(msg.GetSecondDataByte() == 0);
    }

    SUBCASE("Test status messages")
    {
        auto timeStamp = 12345;
        unsigned char channel = 0;
        unsigned char firstDataByte = 0;
        unsigned char secondDataByte = 0;

        msg = mb::MidiMessage(timeStamp, 0x8, channel, firstDataByte, secondDataByte);
        CHECK(msg.GetType() == mb::EVENT_TYPE::NOTE_OFF);

        msg = mb::MidiMessage(timeStamp, 0x9, channel, firstDataByte, secondDataByte);
        CHECK(msg.GetType() == mb::EVENT_TYPE::NOTE_ON);

        msg = mb::MidiMessage(timeStamp, 0xa, channel, firstDataByte, secondDataByte);
        CHECK(msg.GetType() == mb::EVENT_TYPE::NOTE_AFTERTOUCH);

        msg = mb::MidiMessage(timeStamp, 0xb, channel, firstDataByte, secondDataByte);
        CHECK(msg.GetType() == mb::EVENT_TYPE::CONTROLLER);

        msg = mb::MidiMessage(timeStamp, 0xc, channel, firstDataByte, secondDataByte);
        CHECK(msg.GetType() == mb::EVENT_TYPE::PROGRAM_CHANGE);

        msg = mb::MidiMessage(timeStamp, 0xd, channel, firstDataByte, secondDataByte);
        CHECK(msg.GetType() == mb::EVENT_TYPE::CHANNEL_AFTERTOUCH);

        msg = mb::MidiMessage(timeStamp, 0xe, channel, firstDataByte, secondDataByte);
        CHECK(msg.GetType() == mb::EVENT_TYPE::PITCH_BEND);
    }

    SUBCASE("Test vector constructor")
    {
        auto timeStamp = 12345;
        unsigned char note = 40;
        unsigned char velocity = 100;
        auto data = std::vector<unsigned char>{(0x9 << 4) + 0x0, note, velocity};
        msg = mb::MidiMessage(timeStamp, data);
    }

    SUBCASE("Test setters")
    {
        CHECK(true);
    }
}
