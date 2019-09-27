#pragma once
#include <core_export.h>
namespace mb
{
    enum class EVENT_TYPE
    {
        UNINITIALIZED = 0x0,
        NOTE_OFF = 0x8,
        NOTE_ON = 0x9
    };

    class CORE_EXPORT MidiMessage
    {
    public:
        MidiMessage() = default;
        EVENT_TYPE GetType() const;
        unsigned char GetChannel() const;
        unsigned char GetSecondByte() const;
        unsigned char GetThirdByte() const;
        explicit operator bool()const;

    private:
        EVENT_TYPE m_EventType = EVENT_TYPE::UNINITIALIZED;
        unsigned char m_Channel = 0;
        unsigned char m_SecondByte = 0;
        unsigned char m_ThirdByte = 0;
    };
}


