#pragma once
#include <core_export.h>
#include <unordered_map>

namespace mb
{
    enum class EVENT_TYPE
    {
        UNINITIALIZED = 0x0,
        NOTE_OFF = 0x8,
        NOTE_ON = 0x9,
        NOTE_AFTERTOUCH = 0xa,
        CONTROLLER = 0xb,
        PROGRAM_CHANGE = 0xc,
        CHANNEL_AFTERTOUCH = 0xd,
        PITCH_BEND = 0xe
    };

    class CORE_EXPORT MidiMessage
    {
    public:
        MidiMessage() = default;
        MidiMessage(double timeStamp, std::vector<unsigned char> data);
        MidiMessage(double timeStamp, unsigned char eventType, unsigned char channel, unsigned char firstDataByte, unsigned char secondDataByte = 0);
        MidiMessage(double timeStamp, EVENT_TYPE eventType, unsigned char channel, unsigned char firstDataByte, unsigned char secondDataByte = 0);

        double GetTimeStamp() const;
        EVENT_TYPE GetType() const;
        unsigned char GetChannel() const;
        unsigned char GetFirstDataByte() const;
        unsigned char GetSecondDataByte() const;
        explicit operator bool()const;

    private:
        double m_TimeStamp;
        EVENT_TYPE m_EventType = EVENT_TYPE::UNINITIALIZED;
        unsigned char m_Channel = 0;
        unsigned char m_FirstDataByte = 0;
        unsigned char m_SecondDataByte = 0;

#ifdef _WIN32
#pragma warning( push )
#pragma warning( disable : 4251 )
#endif
        static const std::unordered_map<unsigned char, EVENT_TYPE> m_EventTypeLUT;
#ifdef _WIN32
#pragma warning( pop )
#endif
    };
}


