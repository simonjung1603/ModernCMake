#include "RtMidiInAdapter.h"

mb::RtMidiInAdapter::RtMidiInAdapter() : m_MidiImplementation(std::make_unique<RtMidiIn>()), m_OpenPort({false, 0})
{
    const auto callback = [](double timeStamp, std::vector<unsigned char>* message, void* userData)
    {
        const auto midiMessage = std::make_shared<MidiMessage>(timeStamp, *message);
        const auto registeredAdapter = static_cast<RtMidiInAdapter*>(userData);
        registeredAdapter->m_Callback(midiMessage);
    };
    m_MidiImplementation->setCallback(callback, this);
}

void mb::RtMidiInAdapter::SetMessageCallback(std::function<void(std::shared_ptr<MidiMessage>)> callback)
{
    m_Callback = callback;
}

unsigned mb::RtMidiInAdapter::GetPortCount()
{
    return m_MidiImplementation->getPortCount();
}

std::string mb::RtMidiInAdapter::GetPortName(unsigned portId)
{
    return m_MidiImplementation->getPortName(portId);
}

void mb::RtMidiInAdapter::OpenPort(unsigned portId)
{
    if (!m_OpenPort.first)
    {
        m_MidiImplementation->openPort(portId);
        m_OpenPort = {true, portId};
    }
}

void mb::RtMidiInAdapter::ClosePort()
{
    if (m_OpenPort.first)
    {
        m_MidiImplementation->closePort();
        m_OpenPort = {false, 0};
    }
}
