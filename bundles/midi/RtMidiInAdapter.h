#pragma once
#ifdef _WIN32
#pragma warning( push )
#pragma warning( disable : 4251 )
#endif

#include <IMidiInputDevice.h>
#include <memory>
#include <set>
#include <RtMidi.h>
#include <midi_export.h>

namespace mb
{
    class MIDI_EXPORT RtMidiInAdapter : public mb::IMidiInputDevice
    {
    public:
        RtMidiInAdapter();

        void SetMessageCallback(std::function<void(std::shared_ptr<MidiMessage>)> callback) override;
        unsigned GetPortCount() override;
        std::string GetPortName(unsigned portId) override;
        void OpenPort(unsigned portId) override;
        void ClosePort() override;

    private:
        std::unique_ptr<RtMidiIn> m_MidiImplementation;
        std::function<void(std::shared_ptr<mb::MidiMessage>)> m_Callback;
        std::pair<bool, unsigned int> m_OpenPort;
    };
}


#ifdef _WIN32
#pragma warning( pop )
#endif
