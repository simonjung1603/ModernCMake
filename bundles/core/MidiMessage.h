#pragma once
#include <core_export.h>
namespace mb
{
    enum class EVENT_TYPE
    {
        NOTE_OFF = 0x8,
        NOTE_ON = 0x9
    };

    class CORE_EXPORT MidiMessage
    {
    public:
        MidiMessage() = default;

    private:

    };
}
